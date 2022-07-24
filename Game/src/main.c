#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/graphics/Graphics.h>
#include <core/graphics/Mesh.h>
#include <core/graphics/Shader.h>

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
    *output = malloc((length + 1) * sizeof(char));
    int last_char = fread(*output, sizeof(char), length, f);
    (*output)[last_char] = '\0';
    fclose(f);
    return 0;
}

int main()
{
    char *vertex_shader = NULL;
    char *fragment_shader = NULL;
    LoadFile("./Shaders/vertex.glsl", &vertex_shader);
    LoadFile("./Shaders/fragment.glsl", &fragment_shader);
    csGraphicsContext *context = NULL;
    if (csGraphicsContextCreate(&context, 800, 600, "New Window"))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    csMesh *mesh = NULL;
    csMeshCreatePrimitiveTriangle(&mesh);
    csGraphicsContextSetTargetFramerate(context, 60);
    csShader *shader = NULL;
    int result = csShaderLoad(&shader, vertex_shader, fragment_shader);
    if (result)
    {
        printf("An error occurred while loadings the shaders!\n");
        return 1;
    }
    while (csGraphicsUpdate(context))
    {
        csGraphicsFrameStart(context);
        csMeshDraw(mesh, shader);
            // csGraphicsDrawMesh(context,mesh,shader_program);
        float delta = csGraphicsFrameEnd(context);
        printf("delta : %f fps : %i\n", delta, (int)(1.0 / delta));
    }
    csGraphicsContextDestroy(&context);
    csMeshFree(mesh);
    free(vertex_shader);
}