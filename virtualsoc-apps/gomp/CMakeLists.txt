project(gomp)

file(GLOB HEADER "include/*/*.h")
file(GLOB SOURCE "src/*.c")

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})

