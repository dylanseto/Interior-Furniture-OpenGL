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
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;
	vector<glm::vec3> boundingBox;

	glm::mat4 modelMatrix;

	void updateBuffer();
	Mesh_Type type;
	GLuint shaderProgram;

	GLuint VAO, modelVerticesVBO, EBO, modelNormalsVBO, modelUVsVBO;
private:
	bool selected;

	GLuint viewMatrixLoc;
	GLuint projectiontMatrixLoc;
	GLuint modelMatrixLoc;
	GLuint selectedLoc;
	GLuint lamp_positions;
	GLuint lamp_num;

	int textureUnit;

	const GLfloat ROTATION_AMT = (glm::pi<GLfloat>() / 40.0f);
	glm::vec3 sideMove = glm::vec3(0.5, 0, 0);
	glm::vec3 zMove = glm::vec3(0, 0, 0.5);
public:
	Mesh();
	Mesh(vector<GLfloat> vertices, vector<unsigned int> indices);
	~Mesh();

	vector<glm::vec3> getVertices() { return this->vertices; }
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
	
	void setSelected(bool sel){ this->selected = sel; };
	bool getSelected(){ return this->selected; }

	virtual void render() = 0;
};