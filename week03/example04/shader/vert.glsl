// OpenGL 3.3
#version 330

// Input to Vertex Shader
layout (location = 0)  in vec3 vert_Position;
layout (location = 1)  in vec3 vert_Colour;

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Output to Fragment Shader
out vec3 frag_Colour;

void main() {
	// Vertex Colour
	frag_Colour = vert_Colour;

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vec4(vert_Position, 1.0f);
}