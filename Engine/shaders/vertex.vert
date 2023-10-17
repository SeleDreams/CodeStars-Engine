#version 450

layout(location = 0) in vec3 pos;
layout(location = 0) out vec4 vCol;
layout (set = 0,binding=0) uniform uModelBO {mat4 uModel; mat4 uProjection;} uModel;


void main()
{
    gl_Position = uModel.uProjection * uModel.uModel * vec4(pos,1);
    vCol = vec4(clamp(pos,0.0f,1.0f),1.0f);
}