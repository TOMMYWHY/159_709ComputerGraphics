#version 330 core
in vec3 vert_Postion;
void main(){
    gl_Position = vec4(vert_Postion,1.0f);
}