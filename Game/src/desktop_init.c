//
// Created by SeleDreams on 28/09/2024.
//
#include "platform_init.h"
#include <platform-specifics/graphics/GL/GLGraphics.h>

int initialize_engine(void) {
    csGLGraphicsInit();
    return 0;
}

void terminate_engine(void) {

}