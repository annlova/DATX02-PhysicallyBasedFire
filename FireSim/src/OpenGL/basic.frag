#version 330 core
out vec4 color;

uniform sampler2D image;
in vec3 vColorOut;

void main()
{
    color = vec4(vColorOut.xyz, 1.0f);
} 
