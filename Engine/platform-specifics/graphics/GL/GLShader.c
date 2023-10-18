#include "GLShader.h"
#include <core/graphics/Shader.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core/memory/pool_allocator.h"
#include "GLShaderConverter.h"
#include <assert.h>

int csGLShaderProgramCreate(csShader *shader)
{
    GLuint program = glCreateProgram();

    if (!program)
    {
        printf("An error occurred while creating the shader program : %i\n",glGetError());
        return 1;
    }
    ((glShader*)shader)->program = program;
    return 0;
}

int csGLShaderLoad(csShader *shader, const uint32_t *shader_data, size_t shader_size, GLenum shader_type)
{
    GLuint shader_index = glCreateShader(shader_type);
    const char *final_shader = ConvertShader(shader_data,shader_size);
    //printf("%s\n",final_shader);
    GLint length = strlen(final_shader);
    glShaderSource(shader_index, 1, &final_shader, &length);
    csFree((void*)final_shader,length + 1);

    glCompileShader(shader_index);
    GLint result = 0;
    GLchar error[1024] = {0};
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(shader_index, sizeof(error), NULL, error);
        printf("Error when compiling shader %i : %s\n", shader_type, error);
        return 1;
    }
    glAttachShader(((glShader*)shader)->program, shader_index);
    return 0;
}

csShader *csShaderCreate()
{
    return csMalloc(sizeof(glShader));
}

void csShaderDestroy(csShader *shader)
{
    csFree(shader,sizeof(glShader));
}
void error_callback(void *userdata, const char *error)
{
    fprintf(stderr,"An error occurred while using spirv-cross : %s\n",error);
}

int csShaderLoad(csShader *shader, const uint32_t *vertex_shader_data,size_t vertex_shader_size, const uint32_t *fragment_shader_data,size_t fragment_shader_size)
{
    if (csGLShaderProgramCreate(shader))
    {
        return 1;
    }
    if (csGLShaderLoad(shader, vertex_shader_data,vertex_shader_size, GL_VERTEX_SHADER))
    {
        return 2;
    }
    if (csGLShaderLoad(shader, fragment_shader_data, fragment_shader_size, GL_FRAGMENT_SHADER))
    {
        return 3;
    }
    
    GLint result = 0;
    GLchar error[1024] = {0};
    glLinkProgram(((glShader*)shader)->program);
    glGetProgramiv(((glShader*)shader)->program, GL_LINK_STATUS, &result);
    if (!result)
    {
        GLint size;
        glGetProgramInfoLog(((glShader*)shader)->program, sizeof(error), &size, error);
        printf("Error when linking shader program : %s\n", error);
        return 1;
    }
    glValidateProgram(((glShader*)shader)->program);
    glGetProgramiv(((glShader*)shader)->program, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(((glShader*)shader)->program, sizeof(error), NULL, error);
        printf("Error when validating shader program : %s\n", error);
        return 2;
    }
    glBindAttribLocation(((glShader*)shader)->program,0,"pos");
    ((glShader*)shader)->uModelTransform = glGetUniformLocation(((glShader*)shader)->program,"uModel.uModel");
    ((glShader*)shader)->uProjection = glGetUniformLocation(((glShader*)shader)->program,"uModel.uProjection");
    GLenum gl_error = glGetError();
    if (gl_error)
    {
        printf("OpenGL Error : 0x%x\n",glGetError());
        return 3;
    }
    return 0;
}