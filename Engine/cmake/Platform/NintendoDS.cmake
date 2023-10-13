set(CMAKE_C_OUTPUT_EXTENSION .o)
set(CMAKE_CXX_OUTPUT_EXTENSION .o)
set(CMAKE_C_FLAGS_DEBUG          "-Og -DDEBUG")
set(CMAKE_C_FLAGS_MINSIZEREL     "-Oz -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE        "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG          "-Og -DDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Oz -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -DNDEBUG")

include(${CMAKE_CURRENT_LIST_DIR}/BlocksDS/BlocksDS.cmake)

set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)

set(CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH OFF)