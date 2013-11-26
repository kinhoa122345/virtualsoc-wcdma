project(hello_world)

add_executable(${PROJECT_NAME} "hello_world.c")
target_link_libraries(${PROJECT_NAME} simulator)

add_executable(${PROJECT_NAME}_omp "hello_omp_world.c")
target_link_libraries(${PROJECT_NAME}_omp simulator gomp)
