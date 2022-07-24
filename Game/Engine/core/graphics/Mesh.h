#ifndef CS_MESH_H
#define CS_MESH_H
typedef struct Mesh
{
    float *vertices;
    unsigned int vertices_count;
    unsigned int VAO;
    unsigned int VBO;
} Mesh;

void csMeshCreatePrimitiveTriangle(Mesh **output);
void csMeshFree(Mesh *mesh);
#endif