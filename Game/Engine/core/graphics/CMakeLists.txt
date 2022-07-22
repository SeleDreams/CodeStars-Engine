add_library(core-graphics
Graphics.c
)
set(LINK_TARGETS ${LINK_TARGETS} core-graphics PARENT_SCOPE)