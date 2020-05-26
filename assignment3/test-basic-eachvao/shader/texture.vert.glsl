// OpenGL 3.3
#version 330

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Normal;
in vec4 vert_UV;

//in vec4 vert_Tangent ;
uniform vec4 vert_Tangent = vec4(1.0f,1.0f,1.0f,1.0f);


// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

//uniform vec4 u_Light_Direction = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
//uniform vec4 u_Light_Direction;
out vec4 frag_Position;
out vec3 frag_Normal;
//out vec4 frag_Light_Direction;
// Output to Fragment Shader
out vec4 frag_UV;
out vec3 frag_Tangent;
out vec3 frag_Bitangent;

void main() {
	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------

	// Frag UV
	frag_UV = vert_UV;
	frag_Position = u_View * u_Model * vert_Position;
//	frag_Position =   u_Model * vert_Position;

	// Frag Normal
//	frag_Normal = u_View * u_Model * vert_Normal;
	frag_Normal =  (u_Model * vert_Normal).xyz;

	// Frag Light Position
//	frag_Light_Direction = u_View  * u_Light_Direction;
//	frag_Light_Direction =  u_Light_Direction;
	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------

	frag_Tangent = (u_View * u_Model * vert_Tangent).xyz;
	frag_Bitangent = normalize(cross(frag_Normal, frag_Tangent));

	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}