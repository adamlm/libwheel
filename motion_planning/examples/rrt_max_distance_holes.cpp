#include <fmt/core.h>
#include <fmt/ostream.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <boost/geometry.hpp>
#include <libwheel/motion_planning/external/boost_geometry.hpp>
#include <libwheel/motion_planning/local_planning.hpp>
#include <libwheel/motion_planning/rapidly_exploring_random_trees.hpp>
#include <libwheel/motion_planning/vertex_selection.hpp>

namespace {
auto make_results_directory(std::filesystem::path const &directory_path) -> void {
    if (std::error_code ec; !std::filesystem::create_directories(directory_path, ec)) {
        if (ec.value() == 0) {
            // file exists
            return;
        }

        fmt::print(std::cerr, "fatal: cannot create directory: unkown error: {}\n", ec.value());
    }
}
} // namespace

auto main() -> int {
    namespace wheel_mp = wheel::motion_planning;

    using point_t = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
    using polygon_t = boost::geometry::model::polygon<point_t>;

    polygon_t const search_space{{{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}, {0.0, 0.0}},
                                 {{1.0, 1.0}, {2.0, 1.0}, {2.0, 2.0}, {1.0, 2.0}, {1.0, 1.0}}};
    polygon_t const goal_region{{{4.0, 1.0}, {4.5, 1.0}, {4.5, 1.5}, {4.0, 1.5}, {4.0, 1.0}}};

    static constexpr auto boost_geometry_distance = [](auto const &a, auto const &b) {
        return boost::geometry::distance(a, b);
    };

    struct RrtRecorderVisitor {
        using GraphNode = wheel_mp::GraphNode<point_t>;

        auto on_add_node(GraphNode const &node) const noexcept -> void {
            fmt::print(node_stream.get(), "{};{},{}\n", node.index, node.value.get<0>(), node.value.get<1>());
        }

        auto on_add_edge(GraphNode const &source, GraphNode const &target) const noexcept -> void {
            fmt::print(edge_stream.get(), "{};{}\n", source.index, target.index);
        }

        std::reference_wrapper<std::ofstream> node_stream;
        std::reference_wrapper<std::ofstream> edge_stream;
    };

    std::filesystem::path const results_directory{"search_results"};
    make_results_directory(results_directory);

    std::ofstream tree_nodes_output{results_directory / "search_tree_nodes.csv"};
    std::ofstream tree_edges_output{results_directory / "search_tree_edges.csv"};

    auto const search_result{wheel_mp::search_rrt(
        point_t{0.1, 0.1}, goal_region, wheel_mp::UniformSampler{search_space},
        wheel_mp::closest_vertex_selector{boost_geometry_distance},
        wheel_mp::StraightLinePlanner{search_space, wheel_mp::MaxDistance{0.5}}, wheel_mp::MaxExpansions{100},
        wheel_mp::ExpansionsPerSearch{10}, RrtRecorderVisitor{tree_nodes_output, tree_edges_output})};

    if (!search_result) {
        std::cout << "path not found\n";
        return 1;
    }

    fmt::print("path found\n");

    std::ofstream path_file{results_directory / "planned_path.csv"};
    for (auto const &point : search_result.value()) {
        fmt::print(path_file, "{},{}\n", point.get<0>(), point.get<1>());
    }

    std::ofstream search_space_file{results_directory / "search_space.dsv"};
    fmt::print(search_space_file, "{}", boost::geometry::dsv(search_space, ",", "(", ")", ";", "[", "]", ":"));

    std::ofstream goal_region_file{results_directory / "goal_region.dsv"};
    fmt::print(goal_region_file, "{}", boost::geometry::dsv(goal_region, ",", "(", ")", ";", "[", "]", ":"));

    return 0;

    return 0;
}
