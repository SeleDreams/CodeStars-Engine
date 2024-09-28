# the name of the target operating system
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/Modules")
set(CMAKE_SYSTEM_NAME Generic)
add_definitions(-U_WIN32 -U_MSC_VER)
set(NintendoDS ON)
include(${CMAKE_CURRENT_LIST_DIR}/NintendoDS/NintendoDS.cmake)