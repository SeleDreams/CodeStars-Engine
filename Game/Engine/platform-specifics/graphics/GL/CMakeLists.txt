add_library(gl-graphics
GLGraphics.c
)

set(LINK_TARGETS ${LINK_TARGETS} gl-graphics PARENT_SCOPE)