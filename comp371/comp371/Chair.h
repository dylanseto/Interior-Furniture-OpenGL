#pragma once

#include "Mesh.h"

class Chair : public Mesh
{
public:
	Chair(vector<GLfloat> vertices, vector<unsigned int> indices);
	void render();
};