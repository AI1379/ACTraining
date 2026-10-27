# CMakeLists.txt -- top-level aggregator for the ADS course projects.
#
# It exists so the whole repository can be configured, built and tested from a
# single build tree, and so clangd gets one compile_commands.json:
#
#   cmake -S . -B build          configure every project (build/ is gitignored)
#   cmake --build build          build every project
#   ctest --test-dir build       run every project's tests
#
# The projects live in ads-projects/<name>/ as git submodules and carry their
# own self-contained CMakeLists.txt (compiler standard, flags, options,
# vendored dependencies). This file only adds them; read their CMakeLists.txt
# for project-specific details:
#
#   ads-projects/proj1   mini search engine (mse)        C++17, Catch2
#   ads-projects/proj2   pbds / heap benchmarks          C++20, GoogleTest,
#                                                        Google Benchmark
#
# The standalone single-file sources under training/ and template/ are NOT
# CMake projects -- they are compiled one file at a time (VS Code tasks, g++
# on the command line), so they are deliberately left out of this file.
#
# To add a project: put it under ads-projects/<name>/ and append <name> to
# ADS_PROJECTS below.

cmake_minimum_required(VERSION 3.16)

project(ads-projects
  VERSION 0.1
  LANGUAGES C CXX
  DESCRIPTION "ADS Project Main CMakeLists.txt")

# One compile_commands.json for the whole repository, so clangd works from the
# repository root instead of one project at a time.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enables testing in this directory and below: `ctest --test-dir build` then
# runs the test suites registered by every subproject. Each subproject also
# calls enable_testing()/include(CTest) on its own, so it keeps working when
# configured standalone.
enable_testing()

# Give proj1's ctest tests a "proj1." name prefix when they are configured from
# this aggregator. CMake Tools splits ctest names at
# cmake.ctest.testSuiteDelimiter ("."), so all proj1 tests fold under a single
# "proj1" suite in the Testing view. Configured standalone, proj1 keeps its
# original test names.
set(MSE_TEST_NAME_PREFIX "proj1.")

set(ADS_PROJECTS
    proj1
    proj2)

foreach(proj IN LISTS ADS_PROJECTS)
  if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ads-projects/${proj}/CMakeLists.txt")
    message(FATAL_ERROR
      "ads-projects/${proj} is missing or empty. It is a git submodule: "
      "run `git submodule update --init --recursive` first.")
  endif()
  add_subdirectory("ads-projects/${proj}")
endforeach()
