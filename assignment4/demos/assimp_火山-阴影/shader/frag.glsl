#version 330 core

//in vec4 fragColor;
in vec4 frag_UV;
in vec4 frag_Normal;
in vec4 frag_Position;

out vec4 pixel_Colour;

uniform vec4 u_camera_Postion; //
//uniform vec4 viewPos; //== u_camera_Postion

uniform vec4 Ia = vec4( 0.4f,0.4f,0.4f,0.0f );
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//uniform vec4 light_postion =  vec4(0.0f, 5.0f, 3.2f, 0.0f);
uniform vec4 light_postion;
//uniform vec4 lightPos;

//uniform vec4 light_postion =  vec4(0.0f, 1.0f, -3.2f, 0.0f);


uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f, 0.1f);
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1 ;
uniform sampler2D texture_normal1 ;
uniform vec4 kd = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform float texture_shininess = 32.89743616;



void main()
{


	vec4 Color = texture(texture_diffuse1, frag_UV.xy);
	float ambientStrength = 0.1;
	vec4 ambient = ambientStrength * Color*Ia;

	vec4 norm = normalize(frag_Normal);
//	vec4 norm= (normalize(texture(texture_normal1, frag_UV.xy) * 2.0f - 1.0f));
//	vec3 norm= vec3(normalize(texture(texture_normal1, frag_UV.xy).rgb * 2.0f - 1.0f));

	vec4 lightDir = normalize(light_postion - frag_Position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * Color;

	float specularStrength = 0.5;
	vec4 viewDir = normalize(u_camera_Postion - frag_Position);
	vec4 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), texture_shininess);
	vec4 specular = specularStrength * spec * texture(texture_specular1, frag_UV.xy);

	vec4 result = (ambient + diffuse + specular) * Color;
	pixel_Colour = result;
}