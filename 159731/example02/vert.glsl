// OpenGL 3.3
#version 330

// Input to Vertex Shader
in vec3 vert_Position;

void main() {
	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = vec4(vert_Position, 1.0f);
}