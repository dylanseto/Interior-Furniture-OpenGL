#include "Chair.h"
#include "MeshCreator.h"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"


#include <iostream>
using namespace std;

Chair::Chair() : Mesh()
{
	this->type = Mesh_Type::CHAIR;

	if (MeshCreator::loadOBJ("chair.obj", this->vertices, this->indices))
	{
		cout << "[LOAD] Loaded Chair." << endl;
		this->updateBuffer();

		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6, 0.6, 0.6));
		this->updateMatrix();

		createBoundingBox();
	}
}

void Chair::render()
{
	//Update position
	this->draw();
}