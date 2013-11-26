project(simulator)

file(GLOB HEADER "simulator/*.h")
file(GLOB SOURCE "simulator/*.c")

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})

