#define GLEW_STATIC
#include <iostream>
#include <filesystem>
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <irrKlang\irrKlang.h>

#include "OpenGLWindow.h"
#include "shprogram.h"
#include "FPSCamera.h"
#include "Model.h"

using namespace std;

constexpr GLuint WINDOW_WIDTH = 1200;
constexpr GLuint WINDOW_HEIGHT = 800;

FPSCamera camera(glm::vec3(0.0f, 0.0f, 0.0f));

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

GLfloat lastMouseX = 400; 
GLfloat lastMouseY = 300;

void mouseCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
{
	GLfloat xoffset = xpos - lastMouseX;
	GLfloat yoffset = lastMouseY - ypos;
	lastMouseX = xpos;
	lastMouseY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GLFWAdapter::getInstance().init();
	GLFWAdapter::getInstance().configureVersions(3, 3);

	OpenGLWindow appWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Program");
	appWindow.setAsMainContext();

	glfwSetInputMode(appWindow.getInstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(appWindow.getInstance(), mouseCallback);
	glfwSetCursorPos(appWindow.getInstance(), lastMouseX, lastMouseY);

	glfwSetScrollCallback(appWindow.getInstance(), scroll_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw exception("GLEW Initialization failed");

	ShaderProgram shader(".\\res\\vertexShaderLight.vert", ".\\res\\fragmentShaderLight.frag");
	Model nanosuite(".\\res\\planes\\Boeing727.obj");

	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	soundEngine->play2D(".\\res\\avion.mp3", GL_TRUE);

	//render contexts
	while (!appWindow.shouldWindowClose())
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GLFWAdapter::getInstance().pollEvents();

		appWindow.setProcessInputMethod(processInput);
		appWindow.swapBuffers();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.6f, 1.0f, 1.0f);

		//uncomment to see lines of triangles which make rectangle on the screen
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glm::mat4 model;
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::translate(model, glm::vec3(-10.0f, -30.0f, 0.0f));

		glm::mat4 view;
		view = camera.GetViewMatrix();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

		shader.use();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		nanosuite.draw(shader);
	}
	
	soundEngine->drop(); 
	GLFWAdapter::getInstance().terminate();
	return 0;
}