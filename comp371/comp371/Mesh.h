#pragma once

#include <vector>
#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include <glm.hpp>
#include "gtc/type_ptr.hpp"
#include "mesh_type.h"

using namespace std;

class Mesh
{
protected:
	vector<GLuint> indices;
	vector<GLfloat> vertices;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void updateBuffer();
	Mesh_Type type;

private:
	GLuint VAO, VBO, EBO;
	bool hasPoints;

	GLuint viewMatrixLoc;
	GLuint projectiontMatrixLoc;
	GLuint modelMatrixLoc;
	GLuint shaderProgram;

	const GLfloat ROTATION_AMT = (glm::pi<GLfloat>() / 40.0f);
public:
	Mesh();
	Mesh(vector<GLfloat> vertices, vector<unsigned int> indices);
	~Mesh();

	vector<GLfloat> getVertices() { return this->vertices; }

	void draw();
	void updateMatrix();
	void loadShaders();
	void handleMotion(int key);
	bool hasRendered();
	virtual void render() = 0;
};