cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_COLOR_MAKEFILE ON)
option(BUILD_TESTS "Build the tests." OFF)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

#find_package(SystemC REQUIRED)
#find_package(SimSoc REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

file(GLOB THIRD_PARTY_INC_DIRS "3rd_party/*/include")

include_directories(
  ${THIRD_PARTY_INC_DIRS}
  "virtualsoc/include"
  "fir/include")

add_subdirectory(3rd_party)

add_subdirectory(fir)
add_subdirectory(virtualsoc)

