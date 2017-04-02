#include "Game.h"

#include <iostream>

#include "Mesh.h"
#include "EventHandler.h"
#include "Chair.h"
#include "Toilet.h"

using namespace std;

Toilet* chair;

Game::Game()
{
	this->width = 800;
	this->height = 800;
	this->cam = new camera();
}

void Game::init()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);


	this->window = glfwCreateWindow(width, height, "COMP371 Project", nullptr, nullptr);

	if (this->window == nullptr)
	{
		cout << "Error starting window. Exiting..." << endl;
		getchar();
		glfwTerminate();
	}

	glfwMakeContextCurrent(this->window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		getchar();
		exit(-1);
	}
	//Set up Event handlers
	glfwSetCursorPosCallback(window, EventHandler::cursor_position_callback);
	glfwSetKeyCallback(window, EventHandler::key_callback);
	glfwSetMouseButtonCallback(window, EventHandler::mouse_button_callback);
	glfwSetWindowSizeCallback(window, EventHandler::windowResize_callback);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//TODO: Have mesh creator functions.

	//this->mesh = new Mesh();
	//this->mesh->loadShaders();
	chair = new Toilet();
	chair->loadShaders();

	terrain = new Terrain();
	terrain->loadShaders();
}

void Game::mainLoop()
{
	while (!glfwWindowShouldClose(this->window))
	{
		glfwPollEvents();

		//Draw
		//glDepthFunc(GL_LESS);

		// Clear the colorbuffer
		//glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);

		terrain->draw();
		chair->draw();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

glm::mat4 Game::getProjection()
{
	return glm::perspective(cam->getFOV(), ((float)width / (float)height), 0.1f, 1000.0f);
}

glm::mat4 Game::getView()
{
	return glm::lookAt(cam->getPos(), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}


Game* Game::instance;

Game* Game::getInstance()
{
	if (instance == nullptr)
		instance = new Game();
	return instance;
}