#include "Chair.h"
#include "MeshCreator.h"

#include <iostream>
using namespace std;

Chair::Chair() : Mesh()
{
	this->type = Mesh_Type::CHAIR;

	if (MeshCreator::loadOBJ("chair.obj", this->vertices, this->indices))
	{
		cout << "[LOAD] Loaded Chair." << endl;
		this->updateBuffer();
	}
}

void Chair::render()
{
	//Update position
	this->draw();
}