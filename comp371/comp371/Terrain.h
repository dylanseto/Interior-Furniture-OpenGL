#pragma once

#include "Mesh.h"
#include "TerrainType.h"
#include <string>

class Terrain : public Mesh
{
private:
	int wallTexture;
	int ceilingTexture;
	int floorTexture;
public:
	Terrain();
	void render();
	void updateBuffer();
	void updateTexture();
	void draw();

	void changeWall();
	void changeCeiling();
	void changeFloor();

	int getWall();
	int getCeiling();
	int getFloor();

	static const int VERTEX_COUNT = 128;
	static const int SIZE = 800;
};