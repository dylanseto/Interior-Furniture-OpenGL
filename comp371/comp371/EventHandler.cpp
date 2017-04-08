#include "EventHandler.h"
#include <glm.hpp>
#include "..\glm\gtc\matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "Game.h"

#include <iostream>
#include "Game.h"

#include <thread>

bool EventHandler::GetPosition = false;

void EventHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		Game::getInstance()->getCamera()->rotateRight();
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		Game::getInstance()->getCamera()->rotateLeft();
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		Game::getInstance()->getCamera()->rotateUp();
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		Game::getInstance()->getCamera()->rotateDown();
	}
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		Game::getInstance()->getTerrain()->changeCeiling();
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		Game::getInstance()->getTerrain()->changeWall();
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		Game::getInstance()->getTerrain()->changeFloor();
	}
}

void EventHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		EventHandler::GetPosition = true;
	}
}

void EventHandler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (EventHandler::GetPosition)
	{
		//TODO: place new object.
		EventHandler::GetPosition = false;
	}
}

void EventHandler::windowResize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}