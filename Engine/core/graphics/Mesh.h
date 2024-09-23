#ifndef CS_MESH_H
#define CS_MESH_H
#include "Shader.h"
typedef struct csMesh csMesh;
void csMeshCreatePrimitivePyramid(csMesh **output);
void csMeshFree(csMesh *mesh);
void csMeshDraw(csMesh *mesh, csShader *shader);
#endif
