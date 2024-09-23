#include <stdio.h>
#include <stdlib.h>
#include <CodeStarsEngine.h>
#include <platform-specifics/graphics/GL/GLGraphics.h>
#include <time.h>
#include <unistd.h>

csMat4 transMat;
csMat4 scaleMat;
csMat4 rotMat;
csMat4 proj;
csQuat rotation;

int LoadFile(const char *path, uint32_t **output,size_t *length)
{
    // Open the file.
    if (access(path, F_OK) != 0) {
        printf("Error : the file %s does not exist.\n",path);
        return 1;
    }
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Error: could not open shader file: %s\n", path);
		return 1;
    }

    // Read the file.
    fseek(fp, 0L, SEEK_END);
    unsigned int byteSize = (unsigned int)(ftell(fp));
    if (byteSize == 0) {
        printf("Error : File is empty.\n");
        return 1;
    }
    if (byteSize % 4 != 0) {
        printf("Error: file content is not multiple of 4.\n");
        return 1;
    }

    // Read the data in.
    fseek(fp, 0L, SEEK_SET);
    *output = csMalloc(byteSize);
    if (fread(*output, byteSize, 1, fp) != 1) {
        printf("Error: couldn't read file.\n");
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
    uint32_t *vertex_shader_src = NULL;
    size_t vertex_shader_size = 0;
    uint32_t *fragment_shader_src = NULL;
    size_t fragment_shader_size = 0;
    if (LoadFile("./shaders/vertex.spv", &vertex_shader_src,&vertex_shader_size) || LoadFile("./shaders/fragment.spv", &fragment_shader_src,&fragment_shader_size)) {
        return 1;
    }
    csShader *shader = csMalloc(sizeof(int));
    csGLGraphicsInit();
    csGraphicsContext context = NULL;
    if (csGraphicsContextCreate(&context, 800, 600, "New Window"))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    csMesh *mesh = NULL;
    csMeshCreatePrimitivePyramid(&mesh);
    const int framerate = 60;
    csGraphicsContextSetTargetFramerate(context, framerate);
    int result = 0;// csShaderLoad(shader, vertex_shader_src,vertex_shader_size, fragment_shader_src,fragment_shader_size);
    csFree(vertex_shader_src,sizeof(uint32_t) * vertex_shader_size);
    csFree(fragment_shader_src,sizeof(uint32_t) * fragment_shader_size);
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
    csFree(shader,sizeof(int));
//    csShaderDestroy(shader);
    if (csAllocatedData() > 0) {
        printf("Exited with %llu bytes of leaked data !\n", csAllocatedData());
    }
    return 0;
}
