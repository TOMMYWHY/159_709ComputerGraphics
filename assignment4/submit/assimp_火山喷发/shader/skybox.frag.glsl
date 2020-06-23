#version 330 core
out vec4 FragColor;

in vec3 frag_str;

//uniform samplerCube skybox;
uniform samplerCube u_texture_Map;


void main()
{
//	FragColor = texture(skybox, frag_str);
	FragColor = texture(u_texture_Map, frag_str);
}