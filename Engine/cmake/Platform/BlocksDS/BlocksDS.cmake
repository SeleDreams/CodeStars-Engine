include(${CMAKE_CURRENT_LIST_DIR}/WonderfulToolchain.cmake)
set(BLOCKSDS $ENV{BLOCKSDS})
set(BLOCKSDSEXT $ENV{BLOCKSDSEXT})

if(BLOCKSDS STREQUAL "")
message(FATAL_ERROR "The BLOCKSDS environment variable must be set!")
endif()
if (BLOCKSDSEXT STREQUAL "")
message(FATAL_ERROR "The BLOCKSDSEXT environment variable must be set!")
endif()

set(BLOCKSDS_TOOLS ${BLOCKSDS}/tools)

find_program(NDSTOOL ndstool HINTS ${BLOCKSDS_TOOLS}/ndstool)
find_program(MMUTIL mmutil HINTS ${BLOCKSDS_TOOLS}/mmutil)
find_program(MKFATIMG mkfatimg HINTS ${BLOCKSDS_TOOLS}/mkfatimg)
find_program(MMUTIL mmutil HINTS ${BLOCKSDS_TOOLS}/mmutil)
find_program(GRIT grit HINTS ${BLOCKSDS_TOOLS}/grit)
find_program(DLDITOOL dlditool HINTS ${BLOCKSDS_TOOLS}/dlditool)
find_program(DLDIPATCH dldipatch HINTS ${BLOCKSDS_TOOLS}/dldipatch)
find_program(BIN2C bin2c HINTS ${BLOCKSDS_TOOLS}/bin2c)

file(GLOB BLOCKSDS_LIBRARIES LIST_DIRECTORIES true "${BLOCKSDS}/libs/*/lib" "${BLOCKSDSEXT}/*/lib")
file(GLOB BLOCKSDS_INCLUDES LIST_DIRECTORIES true "${BLOCKSDS}/libs/*/include" "${BLOCKSDSEXT}/*/include")

include(${CMAKE_CURRENT_LIST_DIR}/arm9.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/arm7.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/ndstool.cmake)