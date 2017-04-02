#include "camera.h"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"


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

void camera::rotateRight()
{
	this->pos = glm::rotate(this->pos, 10.0f, vec3(0, 1, 0));
}

void camera::rotateLeft()
{
	this->pos = glm::rotate(this->pos, 10.0f, vec3(0, -1, 0));
}

void camera::rotateUp()
{
	this->pos = glm::rotate(this->pos, 10.0f, vec3(-1, 0, 0));
}

void camera::rotateDown()
{
	this->pos = glm::rotate(this->pos, 10.0f, vec3(1, 0, 0));
}