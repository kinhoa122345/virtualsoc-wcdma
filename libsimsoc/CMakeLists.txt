project(simsoc)

file(GLOB HEADER
  "include/*/*.h"
  "include/*/*/*.h"
  "include/*/*/*/*.h"
  "include/*/*.hpp"
  "include/*/*/*.hpp"
  "include/*/*/*/*.hpp"
  "src/*.h"
  "src/*.hpp")

file(GLOB SOURCE
  "src/*.cpp"
  "src/*/*.cpp"
  "src/*/*/*.cpp")

include_directories("./include" "./src")

add_definitions(
  -DABS_TOP_BUILDDIR=\"${CMAKE_ROOT_DIR}\"
  -DBINDIR=\"${EXECUTABLE_OUTPUT_PATH}\")

add_library(${PROJECT_NAME} ${HEADER} ${SOURCE})

add_subdirectory(utils)
