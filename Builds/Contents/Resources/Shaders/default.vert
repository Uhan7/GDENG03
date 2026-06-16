#version 330 core

layout (location = 0) in vec3 aPos;
uniform vec3 offset;

layout (location = 1) in vec3 aColor;

out vec3 colorToUse;

void main()
{
    gl_Position = vec4(aPos + offset, 1.0);
    colorToUse = aColor;
}