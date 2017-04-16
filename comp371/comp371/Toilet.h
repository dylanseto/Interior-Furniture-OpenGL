#pragma once

#include "Mesh.h"
#include <glm.hpp>

class Toilet : public Mesh
{
public:
	Toilet();
	Toilet(glm::vec3 pos);
	void render();
};