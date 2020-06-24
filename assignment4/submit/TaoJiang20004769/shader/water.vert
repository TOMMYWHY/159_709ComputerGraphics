#version 330 core

layout(location = 0) in vec4 vert_Position;
layout(location = 1) in vec3 vert_Normal;
layout(location = 2) in vec4 vert_UV;
//in vec3 vert_Color;

uniform mat4 u_ModelMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjectionMat;

uniform vec4 waterPlane;

//out vec4 fragColor;
out vec4 frag_Position;
out vec4 frag_UV;

void main()
{
	frag_UV = vert_UV;

//	frag_Position = u_ViewMat *  u_ModelMat * vert_Position;
	frag_Position =  u_ModelMat * vert_Position;

//	frag_Normal = u_ViewMat * u_ModelMat * vert_Normal;
//	frag_Normal = u_ModelMat * vert_Normal;//todo

	gl_Position = u_ProjectionMat * u_ViewMat * u_ModelMat * vert_Position;

}