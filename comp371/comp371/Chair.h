#pragma once

#include "Mesh.h"

#include <glm.hpp>

class Chair : public Mesh
{
public:
	Chair();
	Chair(glm::vec3 pos);
	void render();
};