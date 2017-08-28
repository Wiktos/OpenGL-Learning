#include "OpenGLWindow.h"

using namespace std;

OpenGLWindow::OpenGLWindow(int width, int height, string title)
{
	instance = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (instance == nullptr)
	{
		throw runtime_error("Failed to create window");
	}
	glfwSetFramebufferSizeCallback(instance, default_framebuffer_size_callback);
	glfwWindowHint(GL_LOCATION, 100);
}

void OpenGLWindow::default_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void OpenGLWindow::setAsMainContext()
{
	glfwMakeContextCurrent(instance);
}

GLuint OpenGLWindow::shouldWindowClose()
{
	return glfwWindowShouldClose(instance);
}

void OpenGLWindow::setWindowShouldClose()
{
	glfwSetWindowShouldClose(instance, GL_TRUE);
}

void OpenGLWindow::swapBuffers()
{
	glfwSwapBuffers(instance);
}

void OpenGLWindow::setProcessInputMethod(void(*processInput)(GLFWwindow*))
{
	processInput(instance);
}