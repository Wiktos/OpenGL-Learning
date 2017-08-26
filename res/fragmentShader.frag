#version 330 core
out vec4 texture;

in vec2 TexCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;
  
void main()
{
    texture = mix(texture(texture0, TexCoords), texture(texture1, TexCoords), 0.4);
}
