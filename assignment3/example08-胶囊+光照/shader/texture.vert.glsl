// OpenGL 3.3
#version 330

// Input to Vertex Shader
in vec3 vert_Position;
in vec3 vert_Normal;
in vec2 vert_UV;//texcoords

//in vec4 vert_Tangent ;


// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 frag_Position;
out vec3 frag_Normal;
out vec2 frag_UV;

void main() {
	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------

	// Frag UV
	frag_UV = vert_UV;//texcoords
//	frag_Position = u_View * u_Model * vert_Position;
	frag_Position =  vec3( u_Model * vec4(vert_Position,1.0));

	// Frag Normal
//	frag_Normal = u_View * u_Model * vert_Normal;
	frag_Normal =  vert_Normal;

	gl_Position = u_Projection * u_View * u_Model * vec4(vert_Position,1.0);
}
