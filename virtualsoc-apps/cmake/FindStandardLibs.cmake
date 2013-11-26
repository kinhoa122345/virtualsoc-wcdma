message(STATUS "Searching for Standard Libraries.")

set(StandardLibs_LIBRARIES
  "${CMAKE_SOURCE_DIR}/support/lib/libc.a"
  "${CMAKE_SOURCE_DIR}/support/lib/libgcc.a"
  "${CMAKE_SOURCE_DIR}/support/lib/libm.a")

#message(STATUS "Standard libraries = ${StandardLibs_LIBRARIES}")
