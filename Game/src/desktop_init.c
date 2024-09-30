//
// Created by SeleDreams on 28/09/2024.
//
#include "platform_init.h"
#include <platform-specifics/graphics/GL/GLGraphics.h>
#include <time.h>
#include <core/os_functions.h>

const csFixed effectiveClockFrequency = csFixedFromUInt(CLOCKS_PER_SEC);
clock_t last_time = 0;

csFixed csGetSystemDeltaTime(void) {
    clock_t current = clock();
    clock_t delta = current - last_time;
    last_time = current;
    return csFixedDivUnsigned(csFixedFromUInt(delta), effectiveClockFrequency);
}


int initialize_engine(void) {
    last_time = clock();
    csGLGraphicsInit();

    return 0;
}

void terminate_engine(void) {

}