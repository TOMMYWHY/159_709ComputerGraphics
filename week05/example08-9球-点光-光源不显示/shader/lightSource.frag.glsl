// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_UV;

// Texture
uniform sampler2D u_texture_Map;

// Output from Fragment Shader
out vec4 pixel_Colour;

void main () {
	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour =vec4(1.0,0.0,0.0,1.0);
}


