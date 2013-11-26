# This one is important
set(CMAKE_SYSTEM_NAME Linux)

#THis one not so much
set(CMAKE_SYSTEM_VERSION 1)

# Specify the cross compiler
set(CMAKE_C_COMPILER   "/opt/ensta/pack/virtualsoc/arm-elf-gcc-4.5.3/bin/arm-elf-gcc")
set(CMAKE_CXX_COMPILER "/opt/ensta/pack/virtualsoc/arm-elf-gcc-4.5.3/bin/arm-elf-g++")

# Where is the target environment
set(CMAKE_FIND_ROOT_PATH
  "./cmake"
  "../bin"
  "./support/lib"
  "./support/simulator"
  "../virtualsoc/include")

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
