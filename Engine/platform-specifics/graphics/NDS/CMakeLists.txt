add_library(nds-graphics NDSGraphics.c NDSMesh.c NDSGraphicsFunctions.c)
set_arm9_compile_options(nds-graphics)
target_include_directories(nds-graphics PUBLIC ${PROJECT_SOURCE_DIR} ${INCLUDE_DIRS})
target_link_libraries(${PLATFORM_SPECIFICS}_graphics INTERFACE ${PROJECT_NAME}_core nds-graphics)

target_link_libraries(core-graphics nds-graphics)