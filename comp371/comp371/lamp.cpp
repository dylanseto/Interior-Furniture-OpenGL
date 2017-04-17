#include "lamp.h"
#include "MeshCreator.h"
#include "Game.h"

#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"


#include <iostream>
using namespace std;

lamp::lamp() : Mesh()
{
	this->type = Mesh_Type::LAMP;

	if (MeshCreator::loadOBJ("lamp.obj", this->vertices, this->normals, this->uvs))
	{
		cout << "[LOAD] Loaded Lamp." << endl;
		this->updateBuffer();

		modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
		this->updateMatrix();

		createBoundingBox();
		MeshCreator::loadObjectTexture(this);
	}
}

lamp::lamp(glm::vec3 pos) : Mesh()
{
	this->type = Mesh_Type::LAMP;

	if (MeshCreator::loadOBJ("lamp.obj", this->vertices, this->normals, this->uvs))
	{
		cout << "[LOAD] Loaded Lamp." << endl;
		this->updateBuffer();

		modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
		modelMatrix = glm::translate(modelMatrix, (3.0f*pos));

		this->updateMatrix();

		createBoundingBox();
		MeshCreator::loadObjectTexture(this);
	}
}

void lamp::render()
{
	glUseProgram(shaderProgram);
	MeshCreator::loadObjectTexture(this);
	this->draw();
}