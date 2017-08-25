#version 330 core
out vec4 color;

in vec3 ourColor;
in vec2 TexCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;
  
void main()
{
    color = mix(texture(texture0, TexCoords), texture(texture1, TexCoords), 0.4);
}
