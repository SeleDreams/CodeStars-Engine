#include <stdio.h>
#include <core/graphics/Graphics.h>
int main (int argc, char **argv)
{
    csGraphicsContext context;
    int result = csGraphicsContextInit(&context,1280,720,"New Window");
    if (result)
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    return csGraphicsMainLoop(&context);
}