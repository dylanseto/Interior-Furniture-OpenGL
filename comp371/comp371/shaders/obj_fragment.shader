#version 330 core

in vec3 fragPosition;
in vec2 outUV;
in vec3 outNormal;

out vec4 color;

uniform sampler2D obj_Texture;
uniform bool selected;
uniform vec3 lamp_positions[2];
uniform int lamp_num;

void main()
{
	vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
	vec3 objColour = vec3(texture(obj_Texture, outUV));

	//ambient lighting
	float ambientStrength = 0.15f;
	vec3 ambient_contribution = ambientStrength * lightColour;

	vec3 totalDiffuse;

	for (int i = 0; i != lamp_num; i++)
	{
		//diffuse lighting
		vec3 light_position = lamp_positions[i]; //world coords

		vec3 norm = normalize(outNormal);

		vec3 light_direction = normalize(light_position - fragPosition);
		float incident_degree = max(dot(norm, light_direction), 0.0f);
		vec3 diffuse_contribution = incident_degree * lightColour;
		totalDiffuse += diffuse_contribution;
	}

	vec3 resultantColour = (ambient_contribution + totalDiffuse) * objColour;
	if (selected)
	{
		color = vec4(resultantColour, 1.0f) * vec4(1.5, 1.5, 1.5, 1);
	}
	else
	{
		color = vec4(resultantColour, 1.0f);
	}
} 