#version 330 core

in vec4 frag_UV;//texcoords
in vec4 frag_Position;
in vec4 frag_Normal;

uniform vec4 viewPos;
uniform vec4 lightPos;
//uniform sampler2D texture_diffuse1;
uniform sampler2D material_diffuse ;
uniform sampler2D material_specular ;
uniform sampler2D material_Normal;

out vec4 pixel_Colour;

void main()
{
	vec4 Color = texture(material_diffuse, frag_UV.xy);
	float ambientStrength = 0.1;
	vec4 ambient = ambientStrength * Color;

//	vec4 norm = normalize(frag_Normal);
	vec4 norm= vec4(normalize(texture(material_Normal, frag_UV.xy).rgb * 2.0f - 1.0f), 0.0f);

	vec4 lightDir = normalize(lightPos - frag_Position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * Color;

//	float specularStrength = 0.5;
	vec4 viewDir = normalize(viewPos - frag_Position);
	vec4 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec4 specularStrength =texture(material_specular, frag_UV.xy);
	vec4 specular = specularStrength * spec * Color;

	vec4 result = (ambient + diffuse + specular) * Color;
	pixel_Colour = vec4(result);
	//	pixel_Colour = vec4(1.0f,1.0f,1.0f, 1.0);

}



