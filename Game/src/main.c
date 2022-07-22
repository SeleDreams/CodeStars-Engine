#include <stdio.h>
#include <platform-specifics/graphics/GL/GLGraphics.h>
int main (int argc, char **argv)
{
    csGraphicsContext context;
    csGraphicsContextInit(&context);
    printf("Hello World %p\n", &context);
    csGraphicsContextFree(&context);
    return 0;
}