cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
option(BUILD_TESTS "Build the tests." ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(StandardLibs REQUIRED)

include_directories(
  "."
  "./support"
  "./support/simulator"
  "../virtualsoc/include"
  "./gomp/include")

add_subdirectory(support)
add_subdirectory(gomp)
#add_subdirectory(hello_world)

