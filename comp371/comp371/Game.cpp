#include "Game.h"

#include <iostream>

#include "Mesh.h"
#include "EventHandler.h"
#include "Chair.h"
#include "Toilet.h"
#include "MeshCreator.h"
#include "lamp.h"

using namespace std;

Game::Game()
{
	this->width = 800;
	this->height = 800;
	this->cam = new camera();
	this->selectedIndex = 0;
	this->addedObject = 0;
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
	glfwSetWindowCloseCallback(window, EventHandler::windowClosed_callback);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	terrain = new Terrain();
	terrain->loadShaders();

	if (this->getSelected()  != nullptr)
		this->getSelected()->setSelected(true);
}

void Game::close()
{
	delete cam;
	delete terrain;

	MeshCreator::walls.clear();
	MeshCreator::ceilings.clear();
	MeshCreator::floors.clear();
}

void Game::mainLoop()
{
	while (!glfwWindowShouldClose(this->window))
	{
		glfwPollEvents();

		// Clear the colorbuffer
		//glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);

		terrain->draw();
		for (Mesh* mesh : objects)
		{
			mesh->draw();
		}

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

glm::mat4 Game::getProjection()
{
	return glm::perspective(cam->getFOV(), ((float)width / (float)height), 0.5f, 7.0f);
}

glm::mat4 Game::getView()
{
	return glm::lookAt(cam->getPos(), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

Mesh* Game::getSelected()
{
	if (objects.empty()) return nullptr;
	else return objects[selectedIndex];
}

void Game::moveSelction()
{
	selectedIndex = (selectedIndex + 1) % objects.size();
}

void Game::nextAddedObject()
{
	this->addedObject = (addedObject+1) % NUM_OBJ_TYPES;

	cout << "[ADDED OBJECT SWITCH] Switched to ";
	switch (addedObject)
	{
	case Mesh_Type::CHAIR:
		cout << "chair" << endl;
		break;
	case Mesh_Type::TOILET:
		cout << "toilet." << endl;
		break;
	case Mesh_Type::LAMP:
		cout << "lamp." << endl;
		break;
	}
}

void Game::addObject(vec3 pos)
{
	if (addedObject == Mesh_Type::LAMP && lamps.size() >= 2)
	{
		cout << "[ERROR] Trying to add more than two lamps." << endl;
		return;
	}

	//For now, not using pos.
	Mesh* newObject;
	switch (addedObject)
	{
	case Mesh_Type::CHAIR:
		newObject = new Chair(pos);
		cout << "[ADDED] Added new chair to the scene ";
		break;
	case Mesh_Type::TOILET:
		newObject = new Toilet(pos);
		cout << "[ADDED] Added new toilet to the scene ";
		break;
	case Mesh_Type::LAMP:
		newObject = new lamp(pos);
		lamps.push_back(static_cast<lamp*>(newObject));
		cout << "[ADDED] Added new lamp to the scene ";
		break;
	default:
		newObject = new Toilet(pos);
		cout << "[ADDED] Added new toilet to the scene (because we had no idea what you wanted) ";
		break;
	}
	cout << "at pos (" << pos.x << "," << pos.y << "," << pos.z << ")" << endl;

	newObject->loadShaders();
	objects.push_back(newObject);

	this->getSelected()->setSelected(false);
	this->selectedIndex = objects.size() - 1; //Make newly added object selected.
	this->getSelected()->setSelected(true);
}

vector<vec3> Game::getLampPositions()
{
	vector<vec3> pos;

	for (lamp* l : lamps)
	{
		pos.push_back(l->getPos());
	}
	return pos;
}

void Game::updateLights()
{
	terrain->updateMatrix();

	for (Mesh* obj : objects)
	{
		obj->updateMatrix();
	}
}


Game* Game::instance;

Game* Game::getInstance()
{
	if (instance == nullptr)
		instance = new Game();
	return instance;
}