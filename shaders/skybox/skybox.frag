#version 410 core

out vec4 fragColor;
in vec3 texCoords;

uniform samplerCube skybox;
uniform bool polygonMode;

void main()
{
	if (!polygonMode) fragColor = texture(skybox, texCoords);
}
