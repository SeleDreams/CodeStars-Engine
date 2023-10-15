#ifndef CS_SHADER_H
#define CS_SHADER_H
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
typedef struct csShader csShader;
csShader *csShaderCreate(void);
void csShaderDestroy(csShader *shader);
int csShaderLoad(csShader *shader, const uint32_t *vertex_shader_data,size_t vertex_shader_size,const uint32_t *fragment_shader_data,size_t fragment_shader_size);
#endif
