#pragma once

#include "Mesh.h"
#include <string>
using namespace std;

namespace MeshCreator
{
	bool loadOBJ(string filename, vector<GLfloat> &vertices, vector<GLuint> &indices);

	bool loadCube(vector<GLfloat> &vertices, vector<GLfloat> normals, vector<GLfloat> uvs);
	GLuint createTerrain(string textureName);
}

namespace File_Header
{
	const string VERTICES = "v";
	const string INDICES = "f";
}