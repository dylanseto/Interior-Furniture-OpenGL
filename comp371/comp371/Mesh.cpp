#include "Mesh.h"
#include "Game.h"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"
#include "MeshCreator.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Mesh::Mesh()
{
}

Mesh::Mesh(vector<GLfloat> vertices, vector<unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;
	updateBuffer();
	pos = vec3(0, 0, 0);
}

Mesh::~Mesh()
{

}

void Mesh::updateBuffer()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
}

void Mesh::updateMatrix()
{
	viewMatrixLoc = glGetUniformLocation(shaderProgram, "view_matrix");
	projectiontMatrixLoc = glGetUniformLocation(shaderProgram, "projection_matrix");
	modelMatrixLoc = glGetUniformLocation(shaderProgram, "model_matrix");

	//projectionMatrix = Game::getInstance()->getProjection();
	//viewMatrix = Game::getInstance()->getView();

	glUniformMatrix4fv(projectiontMatrixLoc, 1, GL_FALSE, glm::value_ptr(Game::getInstance()->getProjection()));
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(Game::getInstance()->getView()));
}

void Mesh::draw()
{
	glUseProgram(shaderProgram);

	updateMatrix();
	glUniform1i(glGetUniformLocation(shaderProgram, "obj_Texture"), 1);

	glBindVertexArray(VAO);

	if (!indices.empty())
	{
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)1           // element array buffer offset
			);
	}
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
	if (key == GLFW_KEY_W && pos.y+1 < 3)
	{
		modelMatrix = glm::translate(modelMatrix, vec3(0, 1, 0));

		//adjust bounding box
		for (vec3 bound : boundingBox)
		{
			bound = vec3(modelMatrix*vec4(bound,1));
		}

		pos.y += 1;
		cout << pos.y << endl;
	}
	else if (key == GLFW_KEY_A && pos.x + 1 > -3)
	{
		modelMatrix = glm::translate(modelMatrix, vec3(-1, 0, 0));

		//adjust bounding box
		for (vec3 bound : boundingBox)
		{
			bound = vec3(modelMatrix*vec4(bound, 1));
		}

		pos.x--;
		cout << pos.x << endl;
	}
	else if (key == GLFW_KEY_S && pos.y + 1 > -4)
	{
		modelMatrix = glm::translate(modelMatrix, vec3(0, -1, 0));

		//adjust bounding box
		for (vec3 bound : boundingBox)
		{
			bound = vec3(modelMatrix*vec4(bound, 1));
		}

		pos.y -= 1;
		cout << pos.y << endl;
	}
	else if (key == GLFW_KEY_D && pos.x+1 < 4)
	{
		modelMatrix = glm::translate(modelMatrix, vec3(1, 0, 0));

		//adjust bounding box
		for (vec3 bound : boundingBox)
		{
			bound = vec3(modelMatrix*vec4(bound, 1));
		}

		pos.x++;
		cout << pos.x << endl;
	}
}

void Mesh::createBoundingBox()
{
	float xMax = -2;
	float xMin = 2;
	float yMax = -2;
	float yMin = 2;
	float zMax = -2;
	float zMin = 2;

	for (int i = 0; i != vertices.size(); i+=3)
	{
		float x = vertices[i];
		float y = vertices[i+1];
		float z = vertices[i+2];

		if (x > xMax) xMax = x;
		else if (x < xMin) xMin = x;

		if (y > yMax) yMax = y;
		else if (y < yMin) yMin = y;

		if (z > zMax) zMax = z;
		else if (z < zMin) zMin = z;
	}

	//Front face of bounding box.
	boundingBox.push_back(vec3(xMax, yMax, zMax));
	boundingBox.push_back(vec3(xMax, yMin, zMax));
	boundingBox.push_back(vec3(xMin, yMin, zMax));
	boundingBox.push_back(vec3(xMin, yMax, zMax));

	//Back
	boundingBox.push_back(vec3(xMax, yMax, zMin));
	boundingBox.push_back(vec3(xMax, yMin, zMin));
	boundingBox.push_back(vec3(xMin, yMin, zMin));
	boundingBox.push_back(vec3(xMin, yMax, zMin));
}