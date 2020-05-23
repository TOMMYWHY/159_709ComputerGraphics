#version 330 core

in vec2 frag_UV;//texcoords
in vec3 frag_Position;
in vec3 frag_Normal;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform sampler2D texture_diffuse1;


out vec4 pixel_Colour;

void main()
{
	vec3 Color = texture(texture_diffuse1, frag_UV).rgb;
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * Color;

	vec3 norm = normalize(frag_Normal);
	vec3 lightDir = normalize(lightPos - frag_Position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * Color;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - frag_Position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * Color;

	vec3 result = (ambient + diffuse + specular) * Color;
//	pixel_Colour = vec4(result, 1.0);
	pixel_Colour = vec4(1.0f,1.0f,1.0f, 1.0);

}



