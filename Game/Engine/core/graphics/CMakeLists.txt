add_library(core-graphics
Graphics.c
Mesh.c
)
set(LINK_TARGETS core-graphics ${LINK_TARGETS} PARENT_SCOPE)