#include "Toilet.h"
#include "MeshCreator.h"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"


#include <iostream>
using namespace std;

Toilet::Toilet() : Mesh()
{
	this->type = Mesh_Type::TOILET;

	if (MeshCreator::loadOBJ("toilet.obj", this->vertices, this->indices))
	{
		cout << "[LOAD] Loaded Chair." << endl;
		this->updateBuffer();

		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.4, 0.4));
		this->updateMatrix();
	}
}

void Toilet::render()
{
	//Update position
	this->draw();
}