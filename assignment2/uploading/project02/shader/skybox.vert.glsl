#version 330 core
//layout (location = 0) in vec3 vert_Position;

in vec4 vert_Position;

out vec3 frag_str;

uniform mat4 projection;
uniform mat4 view;

void main()
{
//	frag_str = vert_Position.xyz;
	frag_str = normalize(vert_Position.xyz * vec3(-1.0f, -1.0f, 1.0f));

	gl_Position = projection * view * (vert_Position);
}