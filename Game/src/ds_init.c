#include "platform_init.h"
#include <platform-specifics/graphics/NDS/NDSGraphicsFunctions.h>

int initialize_engine(void) {

    return csNDSGraphicsInit();
}

void terminate_engine(void) {

}