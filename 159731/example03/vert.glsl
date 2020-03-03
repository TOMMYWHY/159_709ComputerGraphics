// OpenGL 3.3
#version 330

// Input to Vertex Shader
in vec3 vert_Position;
in vec3 vert_Colour;

// Output to Fragment Shader
out vec3 frag_Colour;

void main() {
	// Vertex Colour
	frag_Colour = vert_Colour;

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = vec4(vert_Position, 1.0f);
}