// OpenGL 4.0
#version 400

// Input to Fragment Shader
in vec4 frag_Position;
in vec4 frag_Colour;

// Output from Fragment Shader
out vec4 pixel_Colour;

void main () {
	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour = frag_Colour;
}