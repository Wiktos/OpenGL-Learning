#define GLEW_STATIC
#include <iostream>

#include "OpenGLWindow.h"
#include "shprogram.h"

using namespace std;

constexpr GLuint WINDOW_WIDTH = 800;
constexpr GLuint WINDOW_HEIGHT = 600;

void simpleProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"out vec4 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GLFWAdapter::getInstance().init();
	GLFWAdapter::getInstance().configureVersions(3, 3);

	OpenGLWindow appWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Program");
	appWindow.setAsMainContext();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw exception("GLEW Initialization failed");

	ShaderProgram shaderProgram(".\\res\\vertexShader.vert", ".\\res\\fragmentShader.frag");

	GLfloat vertices[] = {
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	GLuint indices[] = {  
		0, 1, 2,   
	};

	GLuint VertexBufferObject;
	GLuint VertexArrayObject;
	GLuint ElementBufferObject;

	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glGenBuffers(1, &ElementBufferObject);

	glBindVertexArray(VertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//render contexts
	while (!appWindow.shouldWindowClose())
	{

		GLFWAdapter::getInstance().pollEvents();

		appWindow.setProcessInputMethod(simpleProcessInput);
		appWindow.swapBuffers();
	
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.5f, 0.8f, 1.0f);

		//uncomment to see lines of triangles which make rectangle on the screen
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		shaderProgram.use();
		glBindVertexArray(VertexArrayObject);
		glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	glDeleteBuffers(1, &VertexBufferObject);
	glDeleteBuffers(1, &ElementBufferObject);
	glDeleteVertexArrays(1, &VertexArrayObject);

	GLFWAdapter::getInstance().terminate();
	return 0;
}