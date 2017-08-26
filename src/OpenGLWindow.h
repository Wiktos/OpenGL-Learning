#pragma once
#include <string>
#include <exception>

#include "GLFWAdapter.h"

class OpenGLWindow
{
	GLFWwindow* instance;
public:
	OpenGLWindow(int width, int height, std::string title);
	void setAsMainContext();
	GLuint shouldWindowClose();
	void setWindowShouldClose();
	void swapBuffers();
	void setProcessInputMethod(void(*processInput)(GLFWwindow*));
	GLFWwindow* getInstance()
	{
		return instance;
	}
private:
	static void default_framebuffer_size_callback(GLFWwindow* window, int width, int height);
};