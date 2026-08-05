#version 330 core

out vec4 FragColor;
in vec2 uvToUse;

uniform sampler2D diffuseTexture;
uniform bool useTexture;
uniform vec3 fallbackColor;

void main()
{
    if (useTexture) FragColor = texture(diffuseTexture, uvToUse);
    else FragColor = vec4(fallbackColor, 1.0);
}