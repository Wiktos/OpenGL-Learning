#define GLEW_STATIC
#include <iostream>
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannel;
	unsigned char* imageData = SOIL_load_image(".\\res\\weiti.png", &width, &height, &nrChannel, SOIL_LOAD_RGB);
	if (imageData == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture01;
	glGenTextures(1, &texture01);

	glBindTexture(GL_TEXTURE_2D, texture01);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(imageData);

	int width2, height2, nrChannel2;
	unsigned char* image2Data = SOIL_load_image(".\\res\\gik.jpg", &width2, &height2, 0, SOIL_LOAD_RGB);
	if(image2Data == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture02;
	glGenTextures(1, &texture02);

	glBindTexture(GL_TEXTURE_2D, texture02);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image2Data);


	GLfloat vertices[] = {
		0.6f,  0.6f,  0.0f,		1.0f,  0.0f,
		-0.6f,  0.6f,  0.0f,	0.0f,  0.0f,
		-0.6f, -0.6f,  0.0f,	0.0f,  1.0f,
		0.6f, -0.6f,  0.0f,		1.0f,  1.0f,
	};

	GLuint indices[] = {  
		0, 1, 3,
		1, 2, 3
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture01);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture02);

		shaderProgram.use();
		shaderProgram.setInt("texture0", 0);
		shaderProgram.setInt("texture1", 1);
		
		glm::mat4 model;
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (GLfloat)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

		shaderProgram.setMat4("model", model);
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);

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