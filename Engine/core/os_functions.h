//
// Created by SeleDreams on 29/09/2024.
//

#ifndef OS_FUNCTIONS_H
#define OS_FUNCTIONS_H
#include <stdint.h>
#include "maths/defines.h"
#include "maths/arithmetic.h"

static inline csFixed csGetTimeInterval(int framerate) {
    return csFixedDiv(csFixedFromInt(1),csFixedFromInt(framerate));
}

extern csFixed csGetDeltaTime(void);

extern csFixed csGetSystemDeltaTime(void);
extern void csUpdateDeltaTime(void);
#endif //OS_FUNCTIONS_H
