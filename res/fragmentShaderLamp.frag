#version 330 core
out vec3 FragColor;

uniform vec3 lampColor;

void main()
{
    FragColor = lampColor; // set all 4 vector values to 1.0
}