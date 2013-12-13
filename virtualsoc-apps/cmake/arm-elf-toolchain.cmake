# This one is important
set(CMAKE_SYSTEM_NAME Linux)

message(STATUS "Searching for arm-elf-gcc")

# The HINTS option should only be used for values computed from the system.
SET(_ARM_ELF_GCC_HINTS
  ${ARM_ELF_GCC_PREFIX}
  ${ARM_ELF_GCC_PREFIX}/bin
  $ENV{ARM_ELF_GCC_PREFIX}
  $ENV{ARM_ELF_GCC_PREFIX}/bin
  ${CMAKE_INSTALL_PREFIX}
  ${CMAKE_INSTALL_PREFIX}/bin
  )

# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
SET(_ARM_ELF_GCC_PATHS
  /opt/ensta/pack/virtualsoc/arm-elf-gcc-4.5.3
  /usr/local/bin
  /usr/bin
  /bin
  )

# This one not so much
set(CMAKE_SYSTEM_VERSION 1)

FIND_FILE(CMAKE_C_COMPILER
  NAMES arm-elf-gcc
  HINTS ${_SIMSOC_HINTS}
  PATHS ${_SIMSOC_PATHS}
)

FIND_PATH(CMAKE_CXX_COMPILER
  NAMES arm-elf-g++
  HINTS ${_SIMSOC_HINTS}
  PATHS ${_SIMSOC_PATHS}
)

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
