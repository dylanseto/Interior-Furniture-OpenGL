#pragma once

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include <glm.hpp>



class EventHandler
{
private:
	static bool GetPosition;
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void windowResize_callback (GLFWwindow* window, int width, int height);
	static void windowClosed_callback(GLFWwindow* window);
};