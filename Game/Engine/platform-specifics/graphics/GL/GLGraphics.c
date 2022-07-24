#include "GLGraphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include "GLFWFunctions.h"
#include <core/graphics/Mesh.h>
#include <string.h>

int csGLGraphicsInitGLEW()
{
    glewExperimental = GL_TRUE;
    return glewInit() != GLEW_OK;
}

void csGraphicsContextSetTargetFramerate(csGraphicsContext *context, int framerate)
{
    context->framerate = framerate + 1;
}

void csGraphicsDrawMesh(csGraphicsContext *context, Mesh *mesh, unsigned int shader_program)
{
    glUseProgram(shader_program);
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_VERTEX_ARRAY,mesh->VBO);
    glDrawArrays(GL_TRIANGLES,0,mesh->vertices_count / 3);
    glBindVertexArray(0);
}

void csMeshCreatePrimitiveTriangle(Mesh **output)
{
    *output = malloc(sizeof(Mesh));
    Mesh *mesh = *output;
    float vertices[] =
        {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f};
    mesh->vertices = malloc(sizeof(vertices));
    mesh->vertices_count = sizeof(vertices) / sizeof(float);
    memcpy(mesh->vertices, vertices, sizeof(vertices));
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices_count * sizeof(float), mesh->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    mesh->VAO = VAO;
    mesh->VBO = VBO;
}

void csMeshFree(Mesh *mesh)
{
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteVertexArrays(1, &mesh->VAO);
    free(mesh->vertices);
    free(mesh);
}

int csGLCreateShaderProgram(GLuint *output)
{
    GLuint shader = glCreateProgram();

    if (!shader)
    {
        printf("An error occurred while creating the shader\n");
        return 1;
    }

    GLint result = 0;
    GLchar error[1024] = {0};
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        printf("Error when linking shader %s\n", error);
        return 1;
    }
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        printf("Error when validating shader %s\n", error);
        return 2;
    }
    *output = shader;
    return 0;
}

int csGLGraphicsLoadShader(csGraphicsContext *context, const char *shader_data, GLenum shader_type, unsigned int *output)
{
    GLuint shader_program = *output;
    if (output == 0)
    {
        if (csGLCreateShaderProgram(&shader_program))
        {
            return 1;
        }
    }
    GLuint shader = glCreateShader(shader_type);
    GLint length = strlen(shader_data);
    glShaderSource(shader, 1, &shader_data, &length);
    glCompileShader(shader);
    GLint result = 0;
    GLchar error[1024] = {0};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        printf("Error when compiling shader %i : %s\n", shader_type, error);
        return 1;
    }
    glAttachShader(shader_program, shader);
    *output = shader_program;
    return 0;
}

int csGraphicsLoadVertexShader(csGraphicsContext *context, const char *shader_data, unsigned int *output)
{
    return csGLGraphicsLoadShader(context, shader_data, GL_VERTEX_SHADER, output);
}

int csGraphicsLoadFragmentShader(csGraphicsContext *context, const char *shader_data, unsigned int *output)
{
    return csGLGraphicsLoadShader(context, shader_data, GL_FRAGMENT_SHADER, output);
}