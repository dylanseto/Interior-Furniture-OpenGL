#include "Chair.h"
#include "MeshCreator.h"

#include <iostream>
using namespace std;

Chair::Chair()
{
	this->type = Mesh_Type::CHAIR;

	if (MeshCreator::loadOBJ("chair.obj", this->vertices, this->indices))
	{
		cout << "[LOAD] Loaded Chair." << endl;
	}
}

void Chair::render()
{
	//UPdate position
	this->draw();
}