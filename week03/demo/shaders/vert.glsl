// OpenGL 3.3
#version 330

// Input to Vertex Shader
//layout (location = 0) in vec3 vert_Position;
//layout (location = 0) in vec3 vert_Position;   // 位置变量的属性位置值为 0
//layout (location = 1) in vec3 vert_Colour;
in vec3 vert_Position;
in vec3 vert_Colour;
//layout (location = 0) in vec3 vert_Position;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 frag_Colour;
void main() {
    frag_Colour = vert_Colour;
//    gl_Position = projMat * viewMat * modelMat * vec4(vert_Position, 1.0f);
    gl_Position =   vec4(vert_Position, 1.0f);
//    gl_Position =  vec4(vert_Position, 1.0f);

}