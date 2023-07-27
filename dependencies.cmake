# Install CMake dependency management script
# The get_cpm.cmake script must be included before CPMAddPackage(...) calls
set(CPM_DOWNLOAD_VERSION 0.38.2)
include(cmake/get_cpm.cmake)

# Packages installed through CPM do not need a find_package(...) call
CPMAddPackage("gh:fmtlib/fmt#10.0.0")
CPMAddPackage("gh:google/googletest#v1.13.0")

CPMAddPackage(NAME Eigen3
  GITLAB_REPOSITORY "libeigen/eigen"
  GIT_TAG 3.4.0
  SYSTEM TRUE
  EXCLUDE_FROM_ALL TRUE
  OPTIONS
    "EIGEN_BUILD_DOC FALSE"
    "EIGEN_BUILD_TESTING FALSE"
    "BUILD_TESTING FALSE"  # Eigen will still build tests if this is unspecified
    "EIGEN_BUILD_PKGCONFIG FALSE"
)

CPMAddPackage(NAME range-v3
  GITHUB_REPOSITORY "ericniebler/range-v3"
  GIT_TAG 0.12.0
  SYSTEM TRUE
  EXCLUDE_FROM_ALL TRUE
  OPTIONS
    "RANGES_CXX_STD 20"
)
