cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_COLOR_MAKEFILE ON)
option(BUILD_TESTS "Build the tests." OFF)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(SystemC REQUIRED)
#find_package(SimSoc REQUIRED)

add_definitions(-std=gnu++0x)

include_directories(
  ${SystemC_INCLUDE_DIRS}
  "DRAMSim2/include"
  "libsimsoc/include"
  "virtualsoc/include"
  "fir/include")

add_subdirectory(DRAMSim2)
add_subdirectory(libsimsoc)

add_subdirectory(fir)
add_subdirectory(virtualsoc)

