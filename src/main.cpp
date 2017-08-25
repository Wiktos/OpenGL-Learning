#include "OpenGLWindow.h"

#include <iostream>

using namespace std;

constexpr GLuint WINDOW_WIDTH = 800;
constexpr GLuint WINDOW_HEIGHT = 600;

void simpleProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GLFWAdapter::getInstance().init();
	GLFWAdapter::getInstance().configureVersions(3, 3);

	OpenGLWindow appWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Program");
	appWindow.setAsMainContext();

	//render contexts
	while (!appWindow.shouldWindowClose())
	{

		GLFWAdapter::getInstance().pollEvents();

		appWindow.setProcessInputMethod(simpleProcessInput);
		appWindow.swapBuffers();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.5f, 0.8f, 1.0f);
	}

	GLFWAdapter::getInstance().terminate();
	return 0;
}