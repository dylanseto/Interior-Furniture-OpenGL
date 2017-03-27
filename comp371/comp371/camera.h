#pragma once

#include "glm.hpp"
using namespace glm;

class camera
{
private:
	vec3 pos;
	float fov;
public:
	camera();
	camera(vec3 pos);

	vec3 getPos();
	float getFOV();

	//TODO: Move camera.
};