#include "Chair.h"

Chair::Chair(vector<GLfloat> vertices, vector<unsigned int> indices) : Mesh(vertices, indices)
{
	this->type = Mesh_Type::CHAIR;
}

void Chair::render()
{

}