#version 330 core

in vec3 skyboxCoord;

out vec4 color;

uniform samplerCube skyboxTexture;

void main()
{
	//color = vec4(1, 1, 1, 1);
	color = texture(skyboxTexture, skyboxCoord);
} 