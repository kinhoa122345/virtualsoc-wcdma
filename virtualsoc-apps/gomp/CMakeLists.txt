project(gomp)

include_directories("." "./config/vsoc")

file(GLOB SOURCE "root.c" "../support/simulator/appsupport.c")

add_definitions(-msoft-float -mcpu=arm7 -Winline)
add_library(${PROJECT_NAME} ${SOURCE})


