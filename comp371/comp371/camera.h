#pragma once

#include "glm.hpp"
using namespace glm;

class camera
{
private:
	vec3 pos;
	float fov;

	vec3 yAxis;
	vec3 xAxis;
	float yRotations;
public:
	camera();
	camera(vec3 pos);

	vec3 getPos();
	float getFOV();

	void rotateRight();
	void rotateLeft();
	void rotateUp();
	void rotateDown();

	//TODO: Move camera.
};