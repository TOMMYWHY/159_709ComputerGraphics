#version 330 core

layout(location = 0) in vec4 vert_Position;
layout(location = 1) in vec4 vert_Normal;
layout(location = 2) in vec4 vert_UV;
//in vec3 vert_Color;

uniform mat4 u_ModelMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjectionMat;

//out vec4 fragColor;
out vec4 frag_Position;
out vec4 frag_Normal;
out vec4 frag_UV;
void main()
{
	frag_UV = vert_UV;

//	frag_Position = u_ViewMat *  u_ModelMat * vert_Position; // 不能计算view，否则 光照随 camera 移动
	frag_Position =  u_ModelMat * vert_Position;

//	frag_Normal = u_ViewMat * u_ModelMat * vert_Normal;
//	frag_Normal = u_ModelMat * vert_Normal;//todo
	frag_Normal = vert_Normal;

	gl_Position = u_ProjectionMat * u_ViewMat * u_ModelMat * vert_Position;

}