#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFWAdapter
{
public:
	static GLFWAdapter& getInstance();
	void init();
	void configureVersions(GLuint majorVersion, GLuint minorVersion);
	void terminate();
	void pollEvents();
private:
	GLFWAdapter() {};
	GLFWAdapter(const GLFWAdapter&) = delete;
	GLFWAdapter& operator=(const GLFWAdapter&) = delete;
};