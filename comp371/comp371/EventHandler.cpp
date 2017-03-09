#include "EventHandler.h"
#include <glm.hpp>
#include "..\glm\gtc\matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "Game.h"

#include <iostream>
#include <thread>

bool EventHandler::GetPosition = false;

void EventHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
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