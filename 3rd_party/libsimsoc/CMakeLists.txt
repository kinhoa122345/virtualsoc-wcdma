project(simsoc)

file(GLOB HEADER
  "include/*/*.h"
  "include/*/*/*.h"
  "include/*/*/*/*.h"
  "include/*/*/*/*/*.h"
  "include/*/*.hpp"
  "include/*/*/*.hpp"
  "include/*/*/*/*.hpp"
  "include/*/*/*/*/*.hpp"
  "src/*.h"
  "src/*.hpp")

file(GLOB SOURCE
  "src/*.cpp"
  "src/*/*.cpp"
  "src/*/*/*.cpp"
  "src/*/*/*/*.cpp")

include_directories("./include" "./src")

add_definitions(
  -DABS_TOP_BUILDDIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
  -DABS_TOP_SRCDIR=\"${CMAKE_CURRENT_SOURCE_DIR}/src\"
  -DBINDIR=\"${EXECUTABLE_OUTPUT_PATH}\"
  -DHAVE_CONFIG_H=1)

add_library(${PROJECT_NAME} ${HEADER} ${SOURCE})

add_subdirectory(utils)
