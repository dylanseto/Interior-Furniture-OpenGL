#version 330 core

in vec3 cord;

out vec4 color;

uniform samplerCube obj_Texture;
uniform bool selected;

void main()
{
	//color = vec4(1, 1, 1, 1);
	if(selected)
	{
		color = texture(obj_Texture, cord) * vec4(1.5,1.5,1.5,1);
	}
	else
	{
		color = texture(obj_Texture, cord);
	}
} 