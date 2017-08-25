#pragma once
#include <glm/glm.hpp>

class ShaderProgram
{
	GLuint program_id; 	// The program ID
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

	// Use the program
	void use() const
	{
		glUseProgram(get_programID());
	}

	// returns program ID
	GLuint get_programID() const
	{
		return program_id;
	}

	void setVec4(const std::string &name, const glm::vec4 &value)
	{
		glUniform4f(glGetUniformLocation(program_id, name.c_str()), value.x, value.y, value.z, value.w);
	}
};