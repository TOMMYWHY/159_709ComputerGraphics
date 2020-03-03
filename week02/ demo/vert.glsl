#version 330 core
in vec3 vert_Postion;
//layout(location = 0) in vec3 vert_Position;
void main(){
    gl_Position = vec4(vert_Postion,1.0f);
}