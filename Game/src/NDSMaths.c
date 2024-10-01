//
// Created by SeleDreams on 30/09/2024.
//
#include <libfixmath/fix16.h>
#include <nds.h>

fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1) {

    return mulf32(inArg0 >> 4,inArg1 >> 4) << 4;
}
fix16_t fix16_div(fix16_t inArg0, fix16_t inArg1) {
    return divf32(inArg0 >> 4,inArg1 >> 4) << 4;
}

fix16_t fix16_sqrt(fix16_t inValue)
{
    return sqrtf32(inValue >> 4) << 4;
}