
#version 330 core
  
layout (location = 0) in vec3 position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec4 color;

void main()
{
    gl_Position = model_matrix*vec4(position.x, position.y, position.z, 1.0);
	color = vec4(1.0 , 0.5, position.z, 1.0);
}