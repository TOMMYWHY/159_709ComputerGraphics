
#version 330

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Normal;
in vec4 vert_UV;//texcoords

//in vec4 vert_Tangent ;


// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 frag_Position;
out vec4 frag_Normal;
out vec4 frag_UV;

void main() {
	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------

	// Frag UV
	frag_UV = vert_UV;//texcoords
		frag_Position =  u_Model * vert_Position;

	// Frag Normal
//		frag_Normal = u_View * u_Model * vert_Normal;
	frag_Normal =  vert_Normal;

	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}
