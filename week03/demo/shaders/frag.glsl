// OpenGL 3.3
#version 330

in vec3 frag_Colour;
// Output from Fragment Shader
out vec4 pixel_Colour;


void main () {
    //----------------------------------------------
    // Fragment Colour
    //----------------------------------------------
//    pixel_Colour = vec4(0.5f, 0.0f, 0.0f, 1.0f);
    pixel_Colour = vec4(frag_Colour, 1.0f);

}