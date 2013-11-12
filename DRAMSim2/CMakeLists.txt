project(dramsim)

file(GLOB HEADER
  "include/*/*.h"
  "include/*/*.hpp"
  "src/*.h"
  "src/*.hpp")

file(GLOB SOURCE
  "src/*.cpp")

include_directories("./include" "./src")

add_library(${PROJECT_NAME} ${HEADER} ${SOURCE})

