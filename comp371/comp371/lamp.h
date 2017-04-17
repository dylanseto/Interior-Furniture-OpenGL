#pragma once

#pragma once

#include "Mesh.h"

#include <glm.hpp>

class lamp : public Mesh
{
public:
	lamp();
	lamp(glm::vec3 pos);
	void render();
};
