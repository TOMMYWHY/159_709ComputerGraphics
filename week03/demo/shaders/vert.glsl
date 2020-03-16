// OpenGL 3.3
#version 330

// Input to Vertex Shader
layout (location = 0) in vec3 vert_Position;

in vec3 vert_Colour;
//layout (location = 0) in vec3 vert_Position;
//uniform mat4 transform;

out vec3 frag_Colour;
void main() {
    frag_Colour = vert_Colour;
    gl_Position = vec4(vert_Position, 1.0f);
//    gl_Position = transform * vec4(vert_Position, 1.0f);

}