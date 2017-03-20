#pragma once

#include "Mesh.h"
#include <string>
using namespace std;

namespace MeshCreator
{
	bool loadOBJ(string filename, vector<GLfloat> &vertices, vector<GLuint> &indices);
	//vector<GLfloat> load3DSFile(string filename);
}

namespace File_Header
{
	const string VERTICES = "v";
	const string INDICES = "f";
}