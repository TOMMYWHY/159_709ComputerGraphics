#version 330 core

layout (location = 0) in vec4 vert_Position;
layout (location = 1) in vec4 vert_Normal;
layout (location = 2) in vec4 vert_UV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
out vec4 frag_UV;

void main()
{
	frag_UV = vert_UV;

	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}