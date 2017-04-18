#version 330 core

in vec3 skyboxCoord;
in vec3 outNormal;

out vec4 color;

uniform samplerCube skyboxTexture;
uniform vec3 lamp_positions[2];
uniform int lamp_num;

void main()
{
	vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
	vec3 objColour = vec3(texture(skyboxTexture, skyboxCoord));

	//ambient lighting
	float ambientStrength = 0.2f;
	vec3 ambient_contribution = ambientStrength * lightColour;

	//diffuse lighting
	vec3 totalDiffuse;

	for (int i = 0; i != lamp_num; i++)
	{
		//diffuse lighting
		vec3 light_position = lamp_positions[i]; //world coords

		vec3 norm = normalize(outNormal);

		vec3 light_direction = normalize(light_position - skyboxCoord);
		float incident_degree = max(dot(norm, light_direction), 0.0f);
		vec3 diffuse_contribution = incident_degree * lightColour;
		totalDiffuse += diffuse_contribution;
	}

	vec3 resultantColour = (ambient_contribution + totalDiffuse) * objColour;

	color = vec4(resultantColour, 1.0f);
	//color = vec4(1, 1, 1, 1);
	//color = texture(skyboxTexture, skyboxCoord);
} 