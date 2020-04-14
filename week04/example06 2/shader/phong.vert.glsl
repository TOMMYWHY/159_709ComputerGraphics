// OpenGL 3.3
#version 330

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Normal;
in vec4 vert_UV;
// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
out vec4 frag_UV;


// Light Source - Directional
uniform vec4 u_Light_Direction = vec4(0.0f, 0.0f, -10.0f, 0.0f);

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_Normal;
out vec4 frag_Light_Direction;

void main() {
	// Frag Position
	frag_Position = u_View * u_Model * vert_Position;

	// Frag Normal
	frag_Normal = u_View * u_Model * vert_Normal;

	// Frag Light Position
	frag_Light_Direction = u_View * u_Light_Direction;

	frag_UV = vert_UV;

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}