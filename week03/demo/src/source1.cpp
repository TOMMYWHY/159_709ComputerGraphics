//
// Created by Tommy on 2020-03-06.
//
#include <iostream>
#include <fstream>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <vector>

//#include "vmath.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#define STEP                    6
#define SAMPLE_CNT              (360/STEP)
/*
 * callbacks
 * */
void on_window_close(GLFWwindow *window){
    cout <<"on_window_close..." <<endl;
}
void on_framebuffer_size(GLFWwindow *window,int width, int height){
    glViewport(0, 0, width, height);
    cout <<"window resize to width:"<<width<<"; height:"<<height <<endl;
}
void onError(int error, const char *description) {
    // Print Error message
    cerr << "Error: " << error << " : " << description << endl;
}
/*
 * create window
 * */
GLFWwindow* create_window( int width =800,int height=600,
                           const char * title ="demo",
                           int major = 3, int minor = 2,
                           GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

//    GLFWmonitor * monitor = NULL; GLFWwindow * share= NULL;
    GLFWwindow *window = glfwCreateWindow(width,height,title,monitor,share);
    if(window == NULL){
        cout << "Failed to Create window" << endl;
        return NULL;
    }
    // callbacks
    glfwSetFramebufferSizeCallback(window,on_framebuffer_size);
    glfwSetWindowCloseCallback(window,on_window_close);
    return window;
}
/*
 * read files
 * */
char * read_shader_file( const char* filename){
// const char* filename = "vert.glsl";

    ifstream input(filename);
    //fstream还有和open()一样的构造函数
    /*ifstream input;
    input.open(filename);*/
    if(!input.good()){
        cerr << "Error: Could not open " << filename <<endl;
        return 0;
    }
    input.seekg(0,ios::end);
    size_t size = input.tellg();
    char * data = new char[size+1]; // 添加一个字符空位 给 '\0'
    input.seekg(0,ios::beg);
    input.read(data, size);
    data[size] = '\0';
    input.close();
    cout <<data <<endl;
    return data;
}

/*
 * load shader
 * */
GLuint checkShader(GLuint shader) {
    // Compile status
    GLint status = 0;

    // Check compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // Error detected
    if(status != GL_TRUE) {
        // Get error message length
        int size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

        // Get error message
        char *message = new char[size];
        glGetShaderInfoLog(shader, size, &size, message);

        // Print error message
        std::cerr << message << std::endl;

        // Delete message
        delete[] message;

        // Return error
        return GL_FALSE;
    }

    // Return success
    return GL_TRUE;
}
GLuint load_shader( GLuint shader_type ,const char* filename){
    char* source = read_shader_file(filename);
    GLuint shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id,1, &source, NULL);
    glCompileShader(shader_id);
    // check v shader
    // Check shaders-02 for errors
    if(checkShader(shader_id) == GL_TRUE) {
        // Log
        cout << "Loaded: " << filename << endl;
    } else {
        // Print Error
        cerr << "Error: could not compile " << filename << endl;
        // Delete shader source
        delete[] source;
        // Return Error
        return 0;
    }
    // Delete shader source
    delete[] source;
    return shader_id;
}
GLuint checkProgram(GLuint program) {
    // Link status
    GLint status = 0;

    // Check link status
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    // Error detected
    if(status != GL_TRUE) {
        // Get error message length
        int size;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);

        // Get error message
        char *message = new char[size];
        glGetProgramInfoLog(program, size, &size, message);

        // Print error message
        std::cerr << message << std::endl;

        // Delete message
        delete[] message;

        // Return error
        return GL_FALSE;
    }

    // Return success
    return GL_TRUE;
}
GLuint loadProgram(const char *vert_file, const char *ctrl_file, const char *eval_file, const char *geom_file, const char *frag_file) {
    // Create new OpenGL program
    GLuint program = glCreateProgram();

    // Shader Handles
    GLuint vert_shader = 0;
    GLuint ctrl_shader = 0;
    GLuint eval_shader = 0;
    GLuint geom_shader = 0;
    GLuint frag_shader = 0;

    // Load Shaders
    if(vert_file != NULL) vert_shader = load_shader(GL_VERTEX_SHADER,          vert_file);
    if(ctrl_file != NULL) ctrl_shader = load_shader(GL_TESS_CONTROL_SHADER,    ctrl_file);
    if(eval_file != NULL) eval_shader = load_shader(GL_TESS_EVALUATION_SHADER, eval_file);
    if(geom_file != NULL) geom_shader = load_shader(GL_GEOMETRY_SHADER,        geom_file);
    if(frag_file != NULL) frag_shader = load_shader(GL_FRAGMENT_SHADER,        frag_file);

    // Attach shaders
    if(vert_shader != 0) glAttachShader(program, vert_shader);
    if(ctrl_shader != 0) glAttachShader(program, ctrl_shader);
    if(eval_shader != 0) glAttachShader(program, eval_shader);
    if(geom_shader != 0) glAttachShader(program, geom_shader);
    if(frag_shader != 0) glAttachShader(program, frag_shader);

    // Check Vertex Shader
    if(vert_shader == 0) {
        // Print Error
        std::cerr << "Error: program missing vertex shader." << std::endl;

        // Delete Shaders
        if(vert_shader != 0) glDeleteShader(vert_shader);
        if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
        if(eval_shader != 0) glDeleteShader(eval_shader);
        if(geom_shader != 0) glDeleteShader(geom_shader);
        if(frag_shader != 0) glDeleteShader(frag_shader);

        // Return Error
        return 0;
    }

    // Check Fragment Shader
    if(frag_shader == 0) {
        // Print Error
        std::cerr << "Error: program missing fragment shader." << std::endl;

        // Delete Shaders
        if(vert_shader != 0) glDeleteShader(vert_shader);
        if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
        if(eval_shader != 0) glDeleteShader(eval_shader);
        if(geom_shader != 0) glDeleteShader(geom_shader);
        if(frag_shader != 0) glDeleteShader(frag_shader);

        // Return Error
        return 0;
    }

    // Link program
    glLinkProgram(program);

    // Delete Shaders (no longer needed)
    if(vert_shader != 0) glDeleteShader(vert_shader);
    if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
    if(eval_shader != 0) glDeleteShader(eval_shader);
    if(geom_shader != 0) glDeleteShader(geom_shader);
    if(frag_shader != 0) glDeleteShader(frag_shader);

    // Check program for errors
    if(checkProgram(program) == GL_TRUE) {
        // Print Log
        std::cout << "Loaded: program" << std::endl;
    } else {
        // Print Error
        std::cerr << "Error: could not link program" << std::endl;

        // Return Error
        return 0;
    }

    // Return program
    return program;
}

#if 0
int main(){

    cout <<"testing...."<<endl;
    return 0;
    }
#endif

#if 1
int main(){
    glfwSetErrorCallback(onError);

    glfwInit();
    if(!glfwInit()){
        cout << "Failed to initialize GLFW!\n";
        return 1;
    }
    GLFWwindow* window = create_window(800,600,"example3...");
    if (window == NULL) {
        // Print Error Message
        cerr << "Error: create window or context failed." << endl;
        // Return Error
        return 1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);

    //===========================================//


    GLuint program_id = loadProgram("shaders/vert.glsl", NULL, NULL, NULL, "shaders/frag.glsl");


    //----------------
    int i = 0;
    float p = 0.0, r = 0.04;
    GLfloat vertex_list[2 * 360 / STEP][3];
    GLfloat color_list[2 * 360 / STEP][3];
    GLuint index_list[360 / STEP];
    for (i = 0; i < SAMPLE_CNT * 2; i += 2)
    {
        p = i * STEP * 3.14 / 180;
        vertex_list[i][0] = cos(p) * r;
        vertex_list[i][2] = sin(p) * r;
        vertex_list[i][1] = 0.5f;
        vertex_list[i + 1][0] = cos(p) * r;
        vertex_list[i + 1][2] = sin(p) * r;
        vertex_list[i + 1][1] = -0.5f;
    }
    /* 确定每个点的坐标*/
    for (i = 0; i < SAMPLE_CNT * 2; i++)
    {
        color_list[i][0] = 0.5f;
        color_list[i][1] = 0.0f;
        color_list[i][2] = 1.0f;

    }
    /* 确定顶面的索引*/
    for (i = 0; i < SAMPLE_CNT; i++)
    {
        index_list[i] = i+2;
    }

    std::cout<<"testing"<<std::endl;
    /*for(int i=0;i<60;i++)
    {
        std::cout<<index_list[i]<<",";
    }*/
    for(int i=0;i<120;i++)
    {
        std::cout<<vertex_list[i][0]<<",";
    }


    // Triangle Vertexes (and colours)
    GLfloat buffer[18];

    buffer[0]  =  0.0f; buffer[1]  =  0.577f; buffer[2]  =  0.0f;
    buffer[3]  =  1.0f; buffer[4]  =  0.0f;   buffer[5]  =  0.0f;

    buffer[6]  =  0.5f; buffer[7]  = -0.289f; buffer[8]  =  0.0f;
    buffer[9]  =  0.0f; buffer[10] =  1.0f;   buffer[11] =  0.0f;

    buffer[12] = -0.5f; buffer[13] = -0.289f; buffer[14] =  0.0f;
    buffer[15] =  0.0f; buffer[16] =  0.0f;   buffer[17] =  1.0f;

    // Triangle Indexes
    GLuint indexes[3];
    indexes[0] = 0;
    indexes[1] = 2;
    indexes[2] = 1;
    // VAO VBO EBO
    GLuint vao, vbo,ebo;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);//vbo 装载入 vao

    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_list) + sizeof(color_list), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_list), vertex_list);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_list), sizeof(color_list), color_list);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(vertex_list)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_list), index_list, GL_STATIC_DRAW);




    //clean
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //--engine--//
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //
        glUseProgram(program_id);
        glBindVertexArray(vao);

//        unsigned int transformLoc = glGetUniformLocation(program_id, "transform");
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * SAMPLE_CNT);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        glDrawElements(GL_TRIANGLE_FAN, SAMPLE_CNT, GL_UNSIGNED_INT, (GLvoid *)(0));
        glDrawElementsBaseVertex(GL_TRIANGLE_FAN, SAMPLE_CNT, GL_UNSIGNED_INT, (GLvoid *)(0),1);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean VAO/VBO/EBO
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(program_id);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
#endif