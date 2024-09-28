# Create an interface library
add_library(${PROJECT_NAME}_libs INTERFACE)

# Add subdirectories
add_subdirectory(libfixmatrix)
add_subdirectory(flecs)

# Set options
option(FLECS_SHARED "" OFF)

# Conditional settings for NintendoDS
if (NintendoDS)
    add_compile_definitions(
            FLECS_CUSTOM_BUILD
            FLECS_MODULE
            FLECS_OS_API_IMPL
            FLECS_SYSTEM
    )
    option(FLECS_PIC "" ON)
    add_definitions(
            -U_WIN32
            -U_MSC_VER
            -DECS_TARGET_POSIX
            -DECS_TARGET_LINUX
    )
    set_arm9_compile_options(flecs_static)
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME}_libs INTERFACE flecs_static)

# Get include directories
get_target_property(FIXMATRIX_INCLUDE_DIRS libfixmatrix INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(FLECS_INCLUDE_DIRS flecs_static INTERFACE_INCLUDE_DIRECTORIES)

# Set include directories
set(INCLUDE_DIRS ${FLECS_INCLUDE_DIRS} ${FIXMATRIX_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME}_libs INTERFACE ${INCLUDE_DIRS})

# Link the main project with the interface library
target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}_libs)
