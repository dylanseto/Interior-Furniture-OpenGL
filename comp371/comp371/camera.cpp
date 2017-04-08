#include "camera.h"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>
using namespace std;


camera::camera() : camera(glm::vec3(0.0f, 0.0f, 1.0f))
{
}

camera::camera(vec3 pos)
{
	this->pos = pos;
	this->fov = 45.0f;

	this->yAxis = vec3(0, 1, 0);
	this->xAxis = vec3(1, 0, 0);
	this->yRotations = 0;
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
	this->pos = glm::translate(vec3(0, 0, 0)) * vec4(this->pos, 1);
	this->pos = glm::rotate(this->pos, glm::radians(10.f), yAxis);
	this->pos = glm::translate(vec3(-0, -0, -0)) * vec4(this->pos, 1);

	this->xAxis = glm::normalize(glm::rotate(this->xAxis, glm::radians(10.f), yAxis));
}

void camera::rotateLeft()
{
	this->pos = glm::translate(vec3(0, 0, 0)) * vec4(this->pos, 1);
	this->pos = glm::rotate(this->pos, glm::radians(-10.f), this->yAxis);
	this->pos = glm::translate(vec3(-0, -0, -0)) * vec4(this->pos, 1);

	this->xAxis = glm::normalize(glm::rotate(this->xAxis, glm::radians(-10.f), yAxis));
}

void camera::rotateUp()
{
	if (yRotations > -80)
	{
		this->pos = glm::translate(vec3(0, 0, 0)) * vec4(this->pos, 1);
		this->pos = glm::rotate(this->pos, glm::radians(-10.f), xAxis);
		this->pos = glm::translate(vec3(-0, -0, -0)) * vec4(this->pos, 1);
		yRotations -= 10;
	}
}

void camera::rotateDown()
{
	if (yRotations < 80)
	{
		this->pos = glm::translate(vec3(0, 0, 0)) * vec4(this->pos, 1);
		this->pos = glm::rotate(this->pos, glm::radians(10.f), xAxis);
		this->pos = glm::translate(vec3(-0, -0, -0)) * vec4(this->pos, 1);
		yRotations += 10;
		cout << yRotations << endl;
	}
}