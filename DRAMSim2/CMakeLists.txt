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

get_target_property(FLAGS ${PROJECT_NAME} COMPILE_FLAGS)
if(FLAGS STREQUAL "FLAGS-NOTFOUND")
  set(FLAGS "")
else()
  set(FLAGS "${FLAGS} ")
endif()
set(FLAGS "${FLAGS}-DLOG_OUTPUT -fPIC")
set_target_properties(${CURRENT_TARGET} PROPERTIES COMPILE_FLAGS ${FLAGS})


