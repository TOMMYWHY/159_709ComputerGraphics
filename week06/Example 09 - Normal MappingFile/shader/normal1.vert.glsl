// OpenGL 3.3
#version 330

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Normal;
in vec4 vert_UV;
in vec4 vert_Tangent;

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Light Source - Directional
uniform vec4 u_Light_Direction = vec4(0.0f, -1.0f, -0.2f, 0.0f);

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_UV;
out vec4 frag_Light_Direction;

out vec3 frag_Normal;
out vec3 frag_Tangent;
out vec3 frag_Bitangent;

void main() {
	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------
	// Normal (Camera Space)
	frag_Normal = (u_View * u_Model * vert_Normal).xyz;

	// Tangent (Camera Space)
	frag_Tangent = (u_View * u_Model * vert_Tangent).xyz;

	// Bitangent (Camera Space)
	frag_Bitangent = normalize(cross(frag_Normal, frag_Tangent));

	// Frag Position (Camera Space)
	frag_Position = u_View * u_Model * vert_Position;

	// Frag UV (Camera Space)
	frag_UV = vert_UV;

	// Frag Light Position (Camera Space)
	frag_Light_Direction = u_View * u_Light_Direction;

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}