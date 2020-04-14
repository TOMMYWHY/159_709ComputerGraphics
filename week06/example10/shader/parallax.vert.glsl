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
uniform vec4 u_Light_Direction = vec4(-0.2f, -1.0f, -1.0f, 0.0f);

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_UV;
out vec4 frag_Light_Direction;
out mat4 i_Tangent;

void main() {
	//----------------------------------------------
	// Calculate Normal-Mapping Matrix
	//----------------------------------------------

	// Normal (Camera Space)
	vec4 normal = u_View * u_Model * vert_Normal;

	// Tangent (Camera Space)
	vec4 tangent = u_View * u_Model * vert_Tangent;

	// Bitangent (Camera Space)
	vec4 bitangent = vec4(normalize(cross(normal.xyz, tangent.xyz)), 0.0);

	// Tangent Matrix (Camera Space -> Tangent Space)
	mat4 m_Tangent = mat4(tangent.x, bitangent.x, normal.x, 0,
						  tangent.y, bitangent.y, normal.y, 0,
						  tangent.z, bitangent.z, normal.z, 0,
						  0,         0,           0,        1);

	// Inverse Tangent Matrix
	i_Tangent = transpose(m_Tangent);

	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------
	// Fragment Position (Tangent Space)
	frag_Position = m_Tangent * u_View * u_Model * vert_Position;

	// Frag UV
	frag_UV = vert_UV;

	// Fragment Light Direction (Tangent Space)
	frag_Light_Direction = m_Tangent * u_View * u_Light_Direction;

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}