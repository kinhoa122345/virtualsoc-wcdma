project(dramsim_trace_based_sim)

add_executable(${PROJECT_NAME} TraceBasedSim.cpp)
target_link_libraries(${PROJECT_NAME} dramsim)
