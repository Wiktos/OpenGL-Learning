#include "GLFWAdapter.h"

GLFWAdapter& GLFWAdapter::getInstance()
{
	static GLFWAdapter glfwAdapter;
	return glfwAdapter;
}

void GLFWAdapter::init()
{
	glfwInit();
}

void GLFWAdapter::configureVersions(GLuint majorVersion, GLuint minorVersion)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

void GLFWAdapter::terminate()
{
	glfwTerminate();
}

void GLFWAdapter::pollEvents()
{
	glfwPollEvents();
}