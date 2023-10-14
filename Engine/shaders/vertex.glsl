#version 100
precision mediump float;
attribute vec3 pos;
uniform mat4 uModelTransform;

void main()
{
    gl_Position = uModelTransform * vec4(pos * 0.001, 1.0);
}