# Create an interface library
add_library(${PROJECT_NAME}_libs INTERFACE)
# Add subdirectories
add_subdirectory(libfixmatrix)


# Set options
option(FLECS_SHARED "" OFF)
set(FLECS_SHARED OFF)

# Conditional settings for NintendoDS
if (NintendoDS)
    add_definitions(
            -DFLECS_CUSTOM_BUILD
            -DFLECS_MODULE
            -DFLECS_PIPELINE
            -DFLECS_SYSTEM
            -DFLECS_NO_OS_API_IMPL
            -UFLECS_OS_API_IMPL
            -U_WIN32
            -U_MSC_VER
            -DECS_TARGET_POSIX
            -DECS_TARGET_LINUX
    )
    option(FLECS_PIC "" ON)
endif()
add_subdirectory(flecs)
if (NintendoDS)
set_arm9_compile_options(flecs_static)
endif ()
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
