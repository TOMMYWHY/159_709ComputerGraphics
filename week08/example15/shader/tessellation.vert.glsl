// OpenGL 4.0
#version 400

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Colour;

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Output to Control Shader
out vec4 ctrl_Position;
out vec4 ctrl_Colour;

void main() {
	//----------------------------------------------
	// Output to Control Shader
	//----------------------------------------------
	// Position
	ctrl_Position = vert_Position;

	// Colour
	ctrl_Colour = vert_Colour;
}
