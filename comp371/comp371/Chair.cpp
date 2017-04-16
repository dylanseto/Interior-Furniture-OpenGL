#include "Chair.h"
#include "MeshCreator.h"
#include "Game.h"

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
		MeshCreator::loadObjectTexture(this);
	}
}

Chair::Chair(glm::vec3 pos) : Mesh()
{
	this->type = Mesh_Type::CHAIR;

	if (MeshCreator::loadOBJ("chair.obj", this->vertices, this->indices))
	{
		cout << "[LOAD] Loaded Chair." << endl;
		this->updateBuffer();

		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6, 0.6, 0.6));
		modelMatrix = glm::translate(modelMatrix, (3.0f*pos));

		this->updateMatrix();

		createBoundingBox();
		MeshCreator::loadObjectTexture(this);
	}
}

void Chair::render()
{
	glUseProgram(shaderProgram);
	MeshCreator::loadObjectTexture(this);
	this->draw();
}