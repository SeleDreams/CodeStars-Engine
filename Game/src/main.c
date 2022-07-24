#include <stdio.h>
#include <core/graphics/Graphics.h>
#include <core/graphics/Mesh.h>
#include <stdlib.h>
#include <string.h>
int LoadFile(const char *path, char **output)
{
    FILE *f = fopen(path, "r");
    if (!f)
    {
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    rewind(f);
    char buffer[length + 1];

    *output = malloc((length + 1) * sizeof(char));
    int last_char = fread(buffer, sizeof(char), length, f);
    buffer[last_char] = '\0';
    memcpy(*output,buffer, length + 1);
    //(*output)[length] = "\0";
    fclose(f);
    return 0;
}

int main(int argc, char **argv)
{
    char *vertex_shader = NULL;
    char *fragment_shader = NULL;
    LoadFile("./Shaders/vertex.glsl", &vertex_shader);
    LoadFile("./Shaders/fragment.glsl", &fragment_shader);
    struct csGraphicsContext *context = NULL;
    if (csGraphicsContextCreate(&context, 800, 600, "New Window"))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    Mesh *mesh = NULL;
    csMeshCreatePrimitiveTriangle(&mesh);
    csGraphicsContextSetTargetFramerate(context, 60);
    unsigned int shader_program = 0;
    if (csGraphicsLoadVertexShader(context, vertex_shader, &shader_program))
    {
        printf("An error occurred while loading the vertex shader!\n");
        return 1;
    }
    if (csGraphicsLoadFragmentShader(context, fragment_shader, &shader_program))
    {
        printf("An error occurred while loading the fragment shader\n");
        return 1;
    }
    while (csGraphicsUpdate(context))
    {
        csGraphicsFrameStart(context);

        csGraphicsDrawMesh(context,mesh,shader_program);

        csGraphicsFrameEnd(context);
    }
    csGraphicsContextDestroy(&context);
    csMeshFree(mesh);
    free(vertex_shader);
}