#include <stdio.h>
#include <stdlib.h>
#include <CodeStarsEngine.h>
#include <platform-specifics/graphics/GL/GLGraphics.h>
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

int main(void)
{
    char *vertex_shader = NULL;
    char *fragment_shader = NULL;
    LoadFile("./Shaders/vertex.glsl", &vertex_shader);
    LoadFile("./Shaders/fragment.glsl", &fragment_shader);
    csGLGraphicsInit();
    csGraphicsContext context = NULL;
    if (csGraphicsContextCreate(&context, 800, 600, "New Window"))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    csMesh *mesh = NULL;
    csMeshCreatePrimitiveTriangle(&mesh);
    const int framerate = 60;
    csGraphicsContextSetTargetFramerate(context, framerate);
    csShader *shader = NULL;
    int result = csShaderLoad(&shader, vertex_shader, fragment_shader);
    free(vertex_shader);
    free(fragment_shader);
    if (result)
    {
        printf("An error occurred while loadings the shaders!\n");
        return 1;
    }
    while (csGraphicsUpdate(context))
    {
        csGraphicsFrameStart(context);
        csMeshDraw(mesh, shader);
        csGraphicsFrameEnd(context);
        csGraphicsWaitForNextFrame(framerate);
       // printf("delta : %f fps : %i\n", delta, (int)(1.0 / delta));
    }
    csGraphicsContextDestroy(&context);
    csMeshFree(mesh);
    printf("Hello World!\n");
    return 0;
}
