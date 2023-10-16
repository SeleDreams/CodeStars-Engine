#version 450

layout(location = 0) in vec3 pos;
layout (set = 0,binding=0) uniform uModelBO {mat4 uModelTransform;} uModel;


void main()
{
    gl_Position = vec4(pos, 1);
}