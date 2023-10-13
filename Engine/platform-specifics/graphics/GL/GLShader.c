#include "GLShader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int csGLShaderProgramCreate(csShader *shader)
{
    GLuint program = glCreateProgram();

    if (!program)
    {
        printf("An error occurred while creating the shader program\n");
        return 1;
    }
    shader->program = program;
    return 0;
}

int csGLShaderLoad(csShader *shader, const char *shader_data, GLenum shader_type)
{
    GLuint shader_index = glCreateShader(shader_type);
    GLint length = strlen(shader_data);
    glShaderSource(shader_index, 1, &shader_data, &length);
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
    glAttachShader(shader->program, shader_index);
    return 0;
}

int csShaderLoad(csShader **shader, const char *vertex_shader_data, const char *fragment_shader_data)
{
    *shader = malloc(sizeof(csShader));
    csShader *new_shader = *shader;
    if (csGLShaderProgramCreate(new_shader))
    {
        return 1;
    }
    if (csGLShaderLoad(new_shader, vertex_shader_data, GL_VERTEX_SHADER))
    {
        return 2;
    }
    if (csGLShaderLoad(new_shader, fragment_shader_data, GL_FRAGMENT_SHADER))
    {
        return 3;
    }
    
    GLint result = 0;
    GLchar error[1024] = {0};
    glLinkProgram(new_shader->program);
    glGetProgramiv(new_shader->program, GL_LINK_STATUS, &result);
    if (!result)
    {
        GLint size;
        glGetProgramInfoLog(new_shader->program, sizeof(error), &size, error);
        printf("Error when linking shader program : %s\n", error);
        return 1;
    }
    glValidateProgram(new_shader->program);
    glGetProgramiv(new_shader->program, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(new_shader->program, sizeof(error), NULL, error);
        printf("Error when validating shader program : %s\n", error);
        return 2;
    }
    return 0;
}