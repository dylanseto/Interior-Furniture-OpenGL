#pragma once

#include "Mesh.h"
#include "Terrain.h"
#include <string>
using namespace std;

enum TextureType
{
	RIGHT,
	LEFT,
	CEILING,
	FLOOR,
	FRONT,
	BACK
};

class textureMap
{
private:
	unsigned char* image;
	int width;
	int height;
public:
	textureMap (unsigned char* image, int width, int height) :
		image(image),
		width(width),
		height(height)
	{
	}

	unsigned char* getImage(){ return this->image; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }

};

namespace MeshCreator
{
	bool loadOBJ(string filename, vector<GLfloat> &vertices, vector<GLuint> &indices);

	bool loadCube(vector<GLfloat> &vertices, vector<GLfloat> normals, vector<GLfloat> uvs);
	GLuint createTerrain(Terrain* terrain);
	textureMap* getImage(TextureType type, int index);

	static vector<textureMap*> walls;
	static vector<textureMap*> floors;
	static vector<textureMap*> ceilings;
}

namespace File_Header
{
	const string VERTICES = "v";
	const string INDICES = "f";
}