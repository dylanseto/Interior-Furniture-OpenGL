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
	vector<glm::vec3> boundingBox;

	glm::mat4 modelMatrix;

	void updateBuffer();
	Mesh_Type type;
	GLuint shaderProgram;

	GLuint VAO, VBO, EBO;
private:
	bool hasPoints;

	GLuint viewMatrixLoc;
	GLuint projectiontMatrixLoc;
	GLuint modelMatrixLoc;

	glm::vec3 pos;

	int textureUnit;

	const GLfloat ROTATION_AMT = (glm::pi<GLfloat>() / 40.0f);
public:
	Mesh();
	Mesh(vector<GLfloat> vertices, vector<unsigned int> indices);
	~Mesh();

	vector<GLfloat> getVertices() { return this->vertices; }
	glm::vec3 getPos(){ return pos; }
	vector<glm::vec3> getBound(){ return boundingBox; }
	Mesh_Type getType(){ return this->type; }

	void draw();
	void updateMatrix();
	void loadShaders();
	void handleMotion(int key);
	bool hasRendered();
	void createBoundingBox();
	void setTextureUnit(int tu){ this->textureUnit = tu; }
	int getTextureUnit(){ return this->textureUnit; }
	virtual void render() = 0;
};