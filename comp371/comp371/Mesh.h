#pragma once

#include <vector>
#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include <glm.hpp>
#include "gtc/type_ptr.hpp"

using namespace std;

enum Mesh_Type
{
	ROTATIONAL,
	TRANSLATIONAL
};

class Mesh
{
protected:
	bool rendered;

	vector<GLfloat> profileCurve;
	vector<GLfloat> windowProfileCurve;
	vector<GLuint> indices;
	vector<GLfloat> vertices;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void updateBuffer();
private:
	Mesh_Type type;
	GLuint VAO, VBO, EBO;
	bool hasPoints;

	GLuint viewMatrixLoc;
	GLuint projectiontMatrixLoc;
	GLuint modelMatrixLoc;
	GLuint shaderProgram;

	const GLfloat ROTATION_AMT = (glm::pi<GLfloat>() / 40.0f);
public:
	Mesh();
	Mesh(Mesh_Type type);
	~Mesh();
	void setType(Mesh_Type);
	Mesh_Type getType();

	vector<GLfloat> getVertices() { return this->vertices; }

	void addProfilePoint(GLfloat x, GLfloat y);
	void draw();
	void updateMatrix();
	void loadShaders();
	void handleMotion(int key);
	bool hasRendered();
	virtual void render() = 0;
};