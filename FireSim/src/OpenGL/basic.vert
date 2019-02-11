#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexCol;


uniform mat4 model;
uniform mat4 projection;

uniform vec3 colorIn;

out vec3 vColorOut;
void main()
{
    gl_Position = projection * model * vec4(vertexPos.xyz, 1.0f);
    vColorOut = colorIn;
}

