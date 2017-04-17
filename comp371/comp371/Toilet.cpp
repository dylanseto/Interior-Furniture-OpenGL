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

	if (MeshCreator::loadOBJ("Toilet.obj", this->vertices, this->normals, this->uvs))
	{
		cout << "[LOAD] Loaded Toilet." << endl;
		this->updateBuffer();

		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.4, 0.4));
		this->updateMatrix();

		createBoundingBox();
		MeshCreator::loadObjectTexture(this);
	}
}

Toilet::Toilet(glm::vec3 pos) : Mesh()
{
	this->type = Mesh_Type::TOILET;

	if (MeshCreator::loadOBJ("Toilet.obj", this->vertices, this->normals, this->uvs))
	{
		cout << "[LOAD] Loaded Toilet." << endl;
		this->updateBuffer();

		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.4, 0.4));
		modelMatrix = glm::translate(modelMatrix, (4.0f*pos));

		this->updateMatrix();

		createBoundingBox();
		MeshCreator::loadObjectTexture(this);
	}
}

void Toilet::render()
{
	glUseProgram(shaderProgram);
	MeshCreator::loadObjectTexture(this);
	//Update position
	this->draw();
}