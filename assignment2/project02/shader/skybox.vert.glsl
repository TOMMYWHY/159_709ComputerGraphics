#version 330 core
layout (location = 0) in vec3 vert_Position;

out vec3 frag_str;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	frag_str = vert_Position;
	gl_Position = projection * view * vec4(vert_Position, 1.0);
}