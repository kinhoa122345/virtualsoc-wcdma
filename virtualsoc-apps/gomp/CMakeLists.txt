project(gomp)

file(GLOB HEADER "include/*/*.h")
file(GLOB SOURCE "src/*.c")

add_definitions(-msoft-float -mcpu=arm7 -Winline)
add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})

