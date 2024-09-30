#include "platform_init.h"
#include <platform-specifics/graphics/NDS/NDSGraphicsFunctions.h>
#include <nds.h>
#include <core/os_functions.h>

volatile uint32_t vblankCount = 0;
uint32_t last_time = 0;

csFixed csGetSystemDeltaTime(void) {
    if (vblankCount == 0) {
        last_time = 0;
    }
    uint32_t current = vblankCount;
    uint32_t delta = current - last_time;
    last_time = current;
    return csFixedDivUnsigned(csFixedFromUInt(delta), csFixedFromUInt(60));
}

void vblank_counter(void) {
    if (vblankCount == UINT32_MAX) {
        vblankCount = 0;
    } else {
        vblankCount++;
    }
}

int initialize_engine(void) {
    setCpuClock(TRUE);
    irqSet(IRQ_VBLANK,vblank_counter);
    defaultExceptionHandler();
    return csNDSGraphicsInit();
}

void terminate_engine(void) {

}