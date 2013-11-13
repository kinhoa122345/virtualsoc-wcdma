project(systemc)

file(GLOB HEADER
  "include/*.h"
  "include/*/*.h"
  "include/*/*/*.h"
  "include/*/*/*/*.h"
  "include/*.hpp"
  "include/*/*.hpp"
  "include/*/*/*.hpp"
  "include/*/*/*/*.hpp")

file(GLOB SOURCE
  "src/*.cpp"
  "src/*/*.cpp"
  "src/*/*/*.cpp"
  "src/*/*/*/*.cpp"
  "src/*.c"
  "src/*/*.c"
  "src/*/*/*.c"
  "src/*/*/*/*.c")

include_directories("./include" "./src")

add_library(${PROJECT_NAME} ${HEADER} ${SOURCE})

