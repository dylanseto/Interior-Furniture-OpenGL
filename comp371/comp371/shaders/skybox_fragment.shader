#version 330 core

in vec3 skyboxCoord;
in vec3 outNormal;

out vec4 color;

uniform samplerCube skyboxTexture;

void main()
{
	vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
	vec3 objColour = vec3(texture(skyboxTexture, skyboxCoord));

	//ambient lighting
	float ambientStrength = 0.2f;
	vec3 ambient_contribution = ambientStrength * lightColour;

	//diffuse lighting
	vec3 light_position = vec3(0.0f, 1.0f, 2.0f); //world coords

	vec3 norm = normalize(outNormal);

	vec3 light_direction = normalize(light_position - skyboxCoord);
	float incident_degree = max(dot(norm, light_direction), 0.0f);
	vec3 diffuse_contribution = incident_degree * lightColour;

	vec3 resultantColour = (ambient_contribution + diffuse_contribution) * objColour;

	color = vec4(resultantColour, 1.0f);
	//color = vec4(1, 1, 1, 1);
	//color = texture(skyboxTexture, skyboxCoord);
} 