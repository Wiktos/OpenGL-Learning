#version 330 core

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 color;	// The color variable has attribute position 1
layout (location = 2) in vec2 texture;
  
out vec3 ourColor; // Output a color to the fragment shader
out vec2 TexCoords;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
    ourColor = color; // Set ourColor to the input color we got from the vertex data
	TexCoords = texture;
} 
