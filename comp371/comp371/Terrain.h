#pragma once

#include "Mesh.h"

class Terrain : public Mesh
{
public:
	Terrain();
	void render();

	static const int VERTEX_COUNT = 128;
	static const int SIZE = 800;
};