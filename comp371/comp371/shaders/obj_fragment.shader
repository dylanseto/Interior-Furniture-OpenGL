#version 330 core

in vec3 cord;

out vec4 color;

uniform samplerCube obj_Texture;

void main()
{
	//color = vec4(1, 1, 1, 1);
	color = texture(obj_Texture, cord);
} 