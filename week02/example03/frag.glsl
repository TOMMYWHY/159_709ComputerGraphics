// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec3 frag_Colour;

// Output from Fragment Shader
out vec4 pixel_Colour;

void main () {
	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour = vec4(frag_Colour, 1.0f);
}