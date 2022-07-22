if (DEFINED USE_GL)
add_subdirectory(GL)
endif()

set(LINK_TARGETS ${LINK_TARGETS} PARENT_SCOPE)