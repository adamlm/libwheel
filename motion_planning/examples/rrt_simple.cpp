#include <boost/geometry.hpp>
#include <boost/geometry/io/io.hpp>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fstream>
#include <iostream>
#include <libwheel/motion_planning/external/boost_geometry.hpp>
#include <libwheel/motion_planning/rapidly_exploring_random_trees.hpp>
#include <string>

using point_t = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
using polygon_t = boost::geometry::model::polygon<point_t>;

namespace {
auto make_results_directory(std::filesystem::path const &directory_path) -> void {
    if (std::error_code ec; !std::filesystem::create_directories(directory_path, ec)) {
        std::string error_string{"unknown error"};
        if (ec.value() == 0) {
            error_string = "file exists";
        }

        fmt::print(std::cerr, "rrt_simple: cannot create directory: {}\n", error_string);
        std::exit(1U);
    }
}
} // namespace

auto main() -> int {
    namespace wheel_mp = wheel::motion_planning;

    polygon_t const search_space{{{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}, {0.0, 0.0}}};
    polygon_t const goal_region{{{1.0, 1.0}, {1.0, 2.0}, {2.0, 2.0}, {2.0, 1.0}, {1.0, 1.0}}};

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

    std::filesystem::path const results_directory{"rrt_simple_results"};
    make_results_directory(results_directory);

    std::ofstream tree_nodes_output{results_directory / "search_tree_nodes.csv"};
    std::ofstream tree_edges_output{results_directory / "search_tree_edges.csv"};
    auto const result = wheel_mp::find_path(search_space, point_t(0.1, 0.1), goal_region,
                                            wheel_mp::SimpleRrt{wheel_mp::MaxExpansions{100U}},
                                            RrtRecorderVisitor{tree_nodes_output, tree_edges_output});

    fmt::print("rrt_simple: searching for path\n");
    if (result) {
        fmt::print("rrt_simple: path found\n");

        std::ofstream path_file{results_directory / "planned_path.csv"};
        for (auto const &point : result.value()) {
            fmt::print(path_file, "{},{}\n", point.get<0>(), point.get<1>());
        }

        std::ofstream search_space_file{results_directory / "search_space.dsv"};
        fmt::print(search_space_file, "{}", boost::geometry::dsv(search_space, ",", "(", ")", ";", "[", "]", ":"));

        std::ofstream goal_region_file{results_directory / "goal_region.dsv"};
        fmt::print(goal_region_file, "{}", boost::geometry::dsv(goal_region, ",", "(", ")", ";", "[", "]", ":"));

        return 0;
    }

    fmt::print("rrt_simple: path not found\n");
    return 1;
}
