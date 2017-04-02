#pragma once

#include "Mesh.h"
#include "TerrainType.h"
#include <string>

class Terrain : public Mesh
{
private:
	TerrainType texture;
public:
	Terrain();
	void render();
	void updateBuffer();
	void draw();

	static const int VERTEX_COUNT = 128;
	static const int SIZE = 800;
};