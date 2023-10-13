#include "Graphics.h"
#include <time.h>

float csGraphicsWaitForNextFrame(int framerate)
{
    static float last_frame_seconds = 0;
    static float current_frame_seconds = 0;
    static float delta;

    delta = 0.0f;

    if (last_frame_seconds == 0)
    {
        last_frame_seconds = ((float)clock()) / CLOCKS_PER_SEC;
    }

    while (1.0 / delta >= framerate)
    {
        double current_frame_seconds = ((float)clock()) / CLOCKS_PER_SEC;
        delta = current_frame_seconds - last_frame_seconds;
    }
    last_frame_seconds = current_frame_seconds;
    return delta;
}