#include "EventHandler.h"
#include "Game.h"
#include "IntersectionHelper.h"

#include <iostream>
#include <glm.hpp>
#include "..\glm\gtc\matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "..\glm\gtx\rotate_vector.hpp"

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
	else if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		if (Game::getInstance()->getSelected() != nullptr)
			Game::getInstance()->getSelected()->setSelected(false);

		Game::getInstance()->moveSelction();
		Game::getInstance()->getSelected()->setSelected(true);
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		Game::getInstance()->nextAddedObject();
	}
	else
	{
		Game::getInstance()->getSelected()->handleMotion(key);
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

		//Calculate Ray
		float width = Game::getInstance()->getWidth();
		float height = Game::getInstance()->getHeight();

		float x = (2.0f * xpos) / width - 1.0f;
		float y = 1.0f - (2.0f * ypos) / height;
		float z = 1.0f;
		vec3 ray_nds = vec3(x, y, z);
		vec4 ray_clip = vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
		vec4 ray_eye = inverse(Game::getInstance()->getProjection()) * ray_clip;
		ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		vec3 ray_wor = vec3(inverse(Game::getInstance()->getView()) * ray_eye);
		ray_wor = normalize(ray_wor);

		cout << "(" << ray_wor.x << "," << ray_wor.y << "," << ray_wor.z << ")" << endl;

		//TODO: find closest edge of room (floor, wall, ceiling)
		//TODO: insersection with other objects
		//Add Object

		vec3 intersection;
		IntersectionHelper::getRayRoomIntersection(ray_wor, Game::getInstance()->getTerrain()->getBound(), intersection);
		//Game::getInstance()->addObject(ray_wor); // temp.
		EventHandler::GetPosition = false;
	}
}

void EventHandler::windowResize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void EventHandler::windowClosed_callback(GLFWwindow* window)
{
	Game::getInstance()->close();
}