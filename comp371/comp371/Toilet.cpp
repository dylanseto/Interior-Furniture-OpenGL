#include "Toilet.h"
#include "MeshCreator.h"

#include <iostream>
using namespace std;

Toilet::Toilet() : Mesh()
{
	this->type = Mesh_Type::TOILET;

	if (MeshCreator::loadOBJ("toilet.obj", this->vertices, this->indices))
	{
		cout << "[LOAD] Loaded Chair." << endl;
		this->updateBuffer();
	}
}

void Toilet::render()
{
	//Update position
	this->draw();
}