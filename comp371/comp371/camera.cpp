#include "camera.h"

camera::camera() : camera(glm::vec3(0.0f, 0.0f, 1.0f))
{
}

camera::camera(vec3 pos)
{
	this->pos = pos;
	this->fov = 45.0f;
}

vec3 camera::getPos()
{
	return this->pos;
}

float camera::getFOV()
{
	return this->fov;
}