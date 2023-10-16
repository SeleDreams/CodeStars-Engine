#include <stdio.h>
#include <stdlib.h>
#include <CodeStarsEngine.h>
#include <platform-specifics/graphics/GL/GLGraphics.h>
#include <time.h>
int LoadFile(const char *path, uint32_t **output,size_t *length)
{

    // Open the file.
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        printf("vksbc error: could not open shader file: %s\n", path);
		return 1;
    }

    // Read the file.
    fseek(fp, 0L, SEEK_END);
    unsigned int byteSize = (unsigned int)(ftell(fp));
    if (byteSize == 0) {
        printf("vksbc error: File is empty.\n");
        return 1;
    }
    if (byteSize % 4 != 0) {
        printf("vksbc error: file content is not multiple of 4.\n");
        return 1;
    }

    // Read the data in.
    fseek(fp, 0L, SEEK_SET);
    *output = csMalloc(byteSize);
    if (fread(*output, byteSize, 1, fp) != 1) {
        printf("vksbc error: couldn't read file.\n");
        return 1;
    }
    *length = byteSize / 4;

    // Close the file
    fclose(fp);
    return 0;
}

int main(void)
{
    csMemPoolAllocatorInit(&csMemPoolAllocatorGlobal,8);
    uint32_t *vertex_shader = NULL;
    size_t vertex_shader_size;
    uint32_t *fragment_shader = NULL;
    size_t fragment_shader_size;
    
    LoadFile("./shaders/vertex.spv", &vertex_shader,&vertex_shader_size);
    LoadFile("./shaders/fragment.spv", &fragment_shader,&fragment_shader_size);
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
    csShader *shader = csShaderCreate();
    int result = csShaderLoad(shader, vertex_shader,vertex_shader_size, fragment_shader,fragment_shader_size);
    csFree(vertex_shader,sizeof(uint32_t) * vertex_shader_size);
    csFree(fragment_shader,sizeof(uint32_t) * fragment_shader_size);
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
    csShaderDestroy(shader);
    printf("Hello World!\n");
    return 0;
}
