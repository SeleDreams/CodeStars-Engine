#ifndef CS_SHADER_H
#define CS_SHADER_H
typedef struct csShader csShader;
int csShaderLoad(csShader **shader, const char *vertex_shader_data,const char* fragment_shader_data);
#endif
