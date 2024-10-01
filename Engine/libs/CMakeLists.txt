# Create an interface library
add_library(${PROJECT_NAME}_libs INTERFACE)
# Add subdirectories



# Set options
option(FLECS_SHARED "" OFF)
set(FLECS_SHARED OFF)
add_definitions(
        -DFLECS_NO_OS_API_IMPL
)
# Conditional settings for NintendoDS
if (NintendoDS)
    add_definitions(
            -U_WIN32
            -U_MSC_VER
            -DECS_TARGET_POSIX
            -DECS_TARGET_LINUX
            -DFLECS_CUSTOM_BUILD
            -DFLECS_LOW_FOOTPRINT
            -DFLECS_PIPELINE
            -DFLECS_SYSTEM
            -DFLECS_MODULE
            #-UFLECS_USE_OS_ALLOC
            -DFIXMATH_FAST_SIN
            -DFIXMATH_SIN_LUT
            -DFIXMATH_NO_ROUNDING
            -DFIXMATH_NO_OVERFLOW
            -DFIXMATH_NO_HARD_DIVISION
    )
    option(FLECS_PIC "" ON)
endif()
add_subdirectory(libfixmatrix)
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
