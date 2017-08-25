#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>

class GLFWAdapter
{
public:
	static GLFWAdapter& getInstance();
	void init();
	void configureVersions(GLuint majorVersion, GLuint minorVersion);
	void terminate();
	void pollEvents();
	GLfloat getTime();
private:
	GLFWAdapter() {};
	GLFWAdapter(const GLFWAdapter&) = delete;
	GLFWAdapter& operator=(const GLFWAdapter&) = delete;
};