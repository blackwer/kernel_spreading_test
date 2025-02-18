cmake_minimum_required(VERSION 3.14)
project(
  spreadkernel
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.11
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(doctest)

add_library(spreadkernel SHARED src/spreadkernel.cpp src/doctest.cpp)
target_include_directories(spreadkernel PUBLIC include)
target_link_libraries(spreadkernel PRIVATE doctest)
target_compile_options(spreadkernel PRIVATE -march=native)

add_executable(run_tests test/run_tests.cpp)
target_link_libraries(run_tests PRIVATE spreadkernel doctest)

include(CTest)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(run_tests)
