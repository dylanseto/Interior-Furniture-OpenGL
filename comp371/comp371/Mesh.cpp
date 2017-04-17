#include "Mesh.h"
#include "Game.h"
#include "MeshCreator.h"
#include "IntersectionHelper.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

Mesh::Mesh()
{
}

Mesh::Mesh(vector<GLfloat> vertices, vector<unsigned int> indices)
{
	//this->vertices = vertices;
	//this->indices = indices;
	updateBuffer();
	pos = vec3(0, 0, 0);
}

Mesh::~Mesh()
{

}

void Mesh::updateBuffer()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &modelVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &modelNormalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelNormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &modelUVsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelUVsVBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::updateMatrix()
{
	viewMatrixLoc = glGetUniformLocation(shaderProgram, "view_matrix");
	projectiontMatrixLoc = glGetUniformLocation(shaderProgram, "projection_matrix");
	modelMatrixLoc = glGetUniformLocation(shaderProgram, "model_matrix");
	selectedLoc = glGetUniformLocation(shaderProgram, "selected");

	//projectionMatrix = Game::getInstance()->getProjection();
	//viewMatrix = Game::getInstance()->getView();

	glUniformMatrix4fv(projectiontMatrixLoc, 1, GL_FALSE, glm::value_ptr(Game::getInstance()->getProjection()));
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(Game::getInstance()->getView()));
	glUniform1i(selectedLoc, this->selected);
}

void Mesh::draw()
{
	glUseProgram(shaderProgram);

	updateMatrix();
	glUniform1i(glGetUniformLocation(shaderProgram, "obj_Texture"), this->textureUnit);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	//if (!indices.empty())
	//{
	//	glDrawElements(
	//		GL_TRIANGLES,      // mode
	//		indices.size(),    // count
	//		GL_UNSIGNED_INT,   // type
	//		(void*)0           // element array buffer offset
	//		);
	//}
	glBindVertexArray(0);
}

void Mesh::loadShaders()
{
	// Read the Vertex Shader code from the file
	string vertex_shader_path = "";// = "shaders/obj_vertex.shader";
	string fragment_shader_path = "";
	if (this->type == Mesh_Type::TERRAIN)
	{
		vertex_shader_path = "shaders/skybox_vertex.shader";
		fragment_shader_path = "shaders/skybox_fragment.shader";
	}
	else
	{
		vertex_shader_path = "shaders/obj_vertex.shader";
		fragment_shader_path = "shaders/obj_fragment.shader";
	}
	string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, ios::in);

	if (VertexShaderStream.is_open()) {
		string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open vertex shader %s. Are you in the right directory ?\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	//Read Fragment Shader
	string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, ios::in);

	if (FragmentShaderStream.is_open()) {
		string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("Impossible to open fragment shader %s. Are you in the right directory ?\n", fragment_shader_path.c_str());
		getchar();
		exit(-1);
	}

	//Compile Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Compile Fragment SHader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char * FragmenentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &FragmenentSourcePointer, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Link Shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(shaderProgram);
}

void Mesh::handleMotion(int key)
{
	if (key == GLFW_KEY_W)
	{
		mat4 tempModel;
		bool up = false;
		if (this->getType() == Mesh_Type::CHAIR || this->getType() == Mesh_Type::TOILET)
		{
			tempModel = glm::translate(modelMatrix, -zMove);
		}
		else
		{
			tempModel = glm::translate(modelMatrix, vec3(0, 0.5, 0));
			up = true;
		}
		vector<vec3> tempBounding = IntersectionHelper::createBoundingBox(vertices, tempModel);

		bool intersect = false;
		if (up)
		{
			intersect = IntersectionHelper::BoxToRoomIntersection(tempBounding, Game::getInstance()->getTerrain()->getBound(), PlayerActionType::ACTION_UP);
		}
		else
		{
			intersect = IntersectionHelper::BoxToRoomIntersection(tempBounding, Game::getInstance()->getTerrain()->getBound(), PlayerActionType::ACTION_FORWARD);
		}

		for (Mesh* obj : Game::getInstance()->getObjects())
		{
			if (obj == this) continue; //skip self

			if (IntersectionHelper::BoxToBoxIntersection(tempBounding, obj->getBound()))
			{
				intersect = true;
				break;
			}
		}

		if (!intersect)
		{
			modelMatrix = tempModel;

			//adjust bounding box
			this->boundingBox = tempBounding;

			pos.y += 1;
		}
	}
	else if (key == GLFW_KEY_A)
	{
		mat4 tempModel = glm::translate(modelMatrix, -sideMove);
		vector<vec3> tempBounding = IntersectionHelper::createBoundingBox(vertices, tempModel);

		bool intersect = IntersectionHelper::BoxToRoomIntersection(tempBounding, Game::getInstance()->getTerrain()->getBound(), PlayerActionType::ACTION_LEFT);

		for (Mesh* obj : Game::getInstance()->getObjects())
		{
			if (obj == this) continue; //skip self

			if (IntersectionHelper::BoxToBoxIntersection(tempBounding, obj->getBound()))
			{
				intersect = true;
				break;
			}
		}

		if (!intersect)
		{
			modelMatrix = tempModel;

			//adjust bounding box
			this->boundingBox = tempBounding;

			pos.y -= 1;
		}
	}
	else if (key == GLFW_KEY_S)
	{
		bool up = false;
		mat4 tempModel;
		if (this->getType() == Mesh_Type::CHAIR || this->getType() == Mesh_Type::TOILET)
		{
			tempModel = glm::translate(modelMatrix, zMove);
		}
		else
		{
			tempModel = glm::translate(modelMatrix, vec3(0, -0.5, 0));
			up = true;
		}

		vector<vec3> tempBounding = IntersectionHelper::createBoundingBox(vertices, tempModel);

		bool intersect = false;
		if (up)
		{
			intersect = IntersectionHelper::BoxToRoomIntersection(tempBounding, Game::getInstance()->getTerrain()->getBound(), PlayerActionType::ACTION_UP);
		}
		else
		{
			intersect = IntersectionHelper::BoxToRoomIntersection(tempBounding, Game::getInstance()->getTerrain()->getBound(), PlayerActionType::ACTION_BACKWARD);
		}

		for (Mesh* obj : Game::getInstance()->getObjects())
		{
			if (obj == this) continue; //skip self

			if (IntersectionHelper::BoxToBoxIntersection(tempBounding, obj->getBound()))
			{
				intersect = true;
				break;
			}
		}

		if (!intersect)
		{
			modelMatrix = tempModel;

			//adjust bounding box
			this->boundingBox = tempBounding;

			pos.y -= 1;
		}
	}
	else if (key == GLFW_KEY_D)
	{
		mat4 tempModel = glm::translate(modelMatrix, sideMove);
		vector<vec3> tempBounding = IntersectionHelper::createBoundingBox(vertices, tempModel);

		/*for (int i = 0; i != boundingBox.size(); i++)
		{
			tempBounding.push_back(vec3(modelMatrix*vec4(boundingBox[i], 1)));
		}*/

		bool intersect = IntersectionHelper::BoxToRoomIntersection(tempBounding, Game::getInstance()->getTerrain()->getBound(), PlayerActionType::ACTION_RIGHT);

		for (Mesh* obj : Game::getInstance()->getObjects())
		{
			if (obj == this) continue; //skip self

			if (IntersectionHelper::BoxToBoxIntersection(tempBounding, obj->getBound()))
			{
				intersect = true;
				break;
			}
		}

		if (!intersect)
		{
			modelMatrix = tempModel;

			//adjust bounding box
			this->boundingBox = tempBounding;

			pos.y -= 1;
		}
	}
	else if (key == GLFW_KEY_X)
	{
		modelMatrix = glm::translate(modelMatrix, vec3(0, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(5.f), vec3(0, 1, 0));
		glm::translate(modelMatrix, vec3(-0, -0, -0));

		createBoundingBox();

		sideMove = glm::translate(mat4(), vec3(0, 0, 0))*vec4(sideMove, 1);
		sideMove = glm::rotate(sideMove, glm::radians(5.f), vec3(0, -1, 0));
		sideMove = glm::translate(mat4(), vec3(-0, -0, -0))*vec4(sideMove, 1);

		zMove = glm::translate(mat4(), vec3(0, 0, 0))*vec4(zMove, 1);
		zMove = glm::rotate(zMove, glm::radians(5.f), vec3(0, -1, 0));
		zMove = glm::translate(mat4(), vec3(-0, -0, -0))*vec4(zMove, 1);
	}
	else if (key == GLFW_KEY_Z)
	{
		modelMatrix = glm::translate(modelMatrix, vec3(0, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(5.f), vec3(0,-1,0));
		glm::translate(modelMatrix, vec3(-0, -0, -0));

		createBoundingBox();

		sideMove = glm::translate(mat4(), vec3(0, 0, 0))*vec4(sideMove,1);
		sideMove = glm::rotate(sideMove, glm::radians(5.f), vec3(0, 1, 0));
		sideMove = glm::translate(mat4(), vec3(-0, -0, -0))*vec4(sideMove, 1);

		zMove = glm::translate(mat4(), vec3(0, 0, 0))*vec4(zMove, 1);
		zMove = glm::rotate(zMove, glm::radians(5.f), vec3(0, 1, 0));
		zMove = glm::translate(mat4(), vec3(-0, -0, -0))*vec4(zMove, 1);
	}
}

void Mesh::createBoundingBox()
{
	if (!boundingBox.empty())
	{
		boundingBox.clear(); //reset vector if not empty.
	}

	float xMax = -2;
	float xMin = 2;
	float yMax = -2;
	float yMin = 2;
	float zMax = -2;
	float zMin = 2;

	for (int i = 0; i != vertices.size(); i++)
	{
		vec3 point = vertices[i];
		vec3 pointTransformed = modelMatrix*vec4(point, 1);

		float x = pointTransformed.x;
		float y = pointTransformed.y;
		float z = pointTransformed.z;

		if (x > xMax) xMax = x;
		else if (x < xMin) xMin = x;

		if (y > yMax) yMax = y;
		else if (y < yMin) yMin = y;

		if (z > zMax) zMax = z;
		else if (z < zMin) zMin = z;
	}

	//Front face of bounding box.
	boundingBox.push_back(vec4(xMax, yMax, zMax,1));
	boundingBox.push_back(vec4(xMax, yMin, zMax, 1));
	boundingBox.push_back(vec4(xMin, yMin, zMax,1));
	boundingBox.push_back(vec4(xMin, yMax, zMax, 1));

	//Back
	boundingBox.push_back(vec4(xMax, yMax, zMin, 1));
	boundingBox.push_back(vec4(xMax, yMin, zMin, 1));
	boundingBox.push_back(vec4(xMin, yMin, zMin, 1));
	boundingBox.push_back(vec4(xMin, yMax, zMin, 1));
}