#include <stdio.h>
#include <core/graphics/Graphics.h>
int main (int argc, char **argv)
{
    csGraphicsContext context;
    if (csGraphicsContextInit(&context))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    return csGraphicsMainLoop(&context);
}