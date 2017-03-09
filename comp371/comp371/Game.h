#pragma once

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\gtc\matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "Mesh.h"

#include <glm.hpp>


class Game
{
private:
	static Game* instance;
	GLFWwindow* window;
	Mesh* mesh; // temp.
	GLuint width, height;
public:
	Game();

	Mesh* getMesh(){ return this->mesh; }

	GLuint getWidth(){ return this->width; }
	void setWidth(GLuint width){ this->width = width;  }
	GLuint getHeight(){ return this->height; }
	void setHeight(GLuint height){ this->height = height; }

	void init();
	void mainLoop();
	void updateShader();

	static Game* getInstance();
};