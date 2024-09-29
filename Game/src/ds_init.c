#include "platform_init.h"
#include <platform-specifics/graphics/NDS/NDSGraphicsFunctions.h>
#include <nds.h>
#include <time.h>
#include <nds/timers.h>
#include <core/os_functions.h>

uint32_t csGetTime(void) {
    return timerElapsed(0);
}

int32_t csGetClockDivider() {
    return BUS_CLOCK / 1024;
}

int initialize_engine(void) {
    setCpuClock(false);
    timerStart(0, ClockDivider_1024, 0,NULL);
    defaultExceptionHandler();
    return csNDSGraphicsInit();
}

void terminate_engine(void) {

}