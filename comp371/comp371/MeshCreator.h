#pragma once

#include "Mesh.h"

namespace MeshCreator
{
	Mesh* createTerrain();
	Mesh* createChair();
	//vector<GLfloat> load3DSFile(string filename);
}

namespace File_Header
{
	const unsigned short VERTICES = 0x4110;
	const unsigned short POLYGON = 0x4120;
}