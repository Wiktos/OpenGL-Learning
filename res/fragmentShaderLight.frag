#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

in vec2 TexCoords;
uniform Material material;

struct Light {
    vec3 position;
	vec3  direction;
    float cutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};

uniform Light light;  

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 viewPos;
  
void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
    
	if(theta > light.cutOff) 
	{       
	  // do lighting calculations
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;   

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

	vec3 result = (ambient + diffuse + specular) * attenuation;
	color = vec4(result, 1.0);
	}
	else  // else, use ambient light so scene isn't completely dark outside the spotlight.
	  color = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);
}
