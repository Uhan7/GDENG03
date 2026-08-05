#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec2 uvToUse;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    uvToUse = aUV;
}