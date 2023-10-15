#ifndef GL_SHADER_CONVERTER
#define GL_SHADER_CONVERTER
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
    const char *ConvertShader(const unsigned int *src,size_t filesize);
#ifdef __cplusplus
}
#endif
#endif