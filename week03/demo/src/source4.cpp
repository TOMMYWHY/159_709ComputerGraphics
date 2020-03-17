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
    ifstream input(filename);
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
//    cout <<data <<endl;
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
    int arr[6] = {1,2,3,4,5,6};
    std::vector<int> v1(&arr[0],&arr[3]) ;
    std::vector<int> v2(&arr[3],&arr[5]);
//    for (int i = 0; i < v1.size(); i++) {
//        std::cout<< v1[i] ;
//    }
    std::vector<int> v3;
    v3.insert(v3.end(),v1.begin(),v1.end());
    v3.insert(v3.end(),v2.begin(),v2.end());
    for (int i = 0; i < v3.size(); i++) {
        std::cout<< v3[i] ;
    }
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

    //===========sphere================================//
    const int Y_SEGMENTS = 50;
    const int X_SEGMENTS = 50;
    const float radius = 0.08;
    const GLfloat  PI = 3.14159265358979323846f;
    std::vector<float> sphereVertices;
    std::vector<float> sphereColorList;
    std::vector<int> sphereIndices;
//    std::vector<float> buffer_all;
    for (int y = 0; y <= Y_SEGMENTS; y++)
    {
        for (int x = 0; x <= X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            sphereVertices.push_back(xPos*radius);
            sphereVertices.push_back(yPos*radius+0.5f);
            sphereVertices.push_back(zPos*radius);
        }
    }

    // sphere color
    for (int i = 0; i < sphereVertices.size();) {
        sphereColorList.push_back(0.9f);
        sphereColorList.push_back(0.4f);
        sphereColorList.push_back(0.2f);
        i = i+3;
    }

    // sphere Indices
    for (int i = 0; i < Y_SEGMENTS; i++)
    {
        for (int j = 0; j < X_SEGMENTS; j++)
        {

            sphereIndices.push_back(i * (X_SEGMENTS+1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);

            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
        }
    }


    //--------cylinder--------
    float p = 0.0, r = 0.04;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    std::vector<float> cylinderVertices;
    std::vector<float> cylinderColorList;
    std::vector<int>   cylinderIndexList;


    for ( i = 0; i < sample_cnt * 2; i += 2)
    {
        p = i * step * 3.14 / 180;
        float xPos = cos(p) * r;
        float zPos = sin(p) * r;
        float yPos = 0.5f;
        cylinderVertices.push_back(xPos);
        cylinderVertices.push_back(yPos);
        cylinderVertices.push_back(zPos);
        float xPos_next = cos(p) * r;
        float zPos_next = sin(p) * r;
        float yPos_next = -0.7f;
        cylinderVertices.push_back(xPos_next);
        cylinderVertices.push_back(yPos_next);
        cylinderVertices.push_back(zPos_next);

    }
    // cylinder color
    for (int i = 0; i < sample_cnt * 2; i++)
    {
        cylinderColorList.push_back(0.9f);
        cylinderColorList.push_back(0.9f);
        cylinderColorList.push_back(0.0f);
    }
    // cylinder  Indices
    for (int i = 0; i < sample_cnt; i++)
    {
        int index = i+2;
        cylinderIndexList.push_back(index) ;
    }
    std::cout<<"testing"<<std::endl;



    GLuint cylinder_vao = 0;
    GLuint cylinder_vbo = 0;
    GLuint cylinder_ebo = 0;
    glGenVertexArrays(1, &cylinder_vao);
    glGenBuffers(1, &cylinder_vbo);
    glGenBuffers(1, &cylinder_ebo);
    glBindVertexArray(cylinder_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_ebo);
    glBufferData(GL_ARRAY_BUFFER, cylinderVertices.size()* sizeof(float) + cylinderColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, cylinderVertices.size()* sizeof(float), &cylinderVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, cylinderVertices.size()* sizeof(float), cylinderColorList.size()* sizeof(float), &cylinderColorList[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(cylinderVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinderIndexList.size()* sizeof(float), &cylinderIndexList[0], GL_STATIC_DRAW);


    GLuint sphere_vao = 0;
    GLuint sphere_vbo = 0;
    GLuint sphere_ebo = 0;
    glGenVertexArrays(1, &sphere_vao);
    glGenBuffers(1, &sphere_vbo);
    glGenBuffers(1, &sphere_ebo);
    glBindVertexArray(sphere_vao);
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ebo);

    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size()* sizeof(float) + sphereColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sphereVertices.size()* sizeof(float), &sphereVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sphereVertices.size()* sizeof(float), sphereColorList.size()* sizeof(float), &sphereColorList[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sphereVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size()* sizeof(float), &sphereIndices[0], GL_STATIC_DRAW);






    //clean
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //--engine--//
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //
        /*glUseProgram(program_id);
        glBindVertexArray(vao);*/



        //cylinder
        glUseProgram(program_id);
        glBindVertexArray(cylinder_vao);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        glDrawElements(GL_TRIANGLE_FAN, SAMPLE_CNT, GL_UNSIGNED_INT, (GLvoid *)(0));
        glDrawElementsBaseVertex(GL_TRIANGLE_FAN, SAMPLE_CNT, GL_UNSIGNED_INT, (GLvoid *)(0),1);
        glBindVertexArray(0);

        // sphere
        glUseProgram(program_id);
        glBindVertexArray(sphere_vao);
        glDrawElements(GL_TRIANGLES, X_SEGMENTS*Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean VAO/VBO/EBO
    glDeleteVertexArrays(1, &cylinder_vao);
    glDeleteBuffers(1, &cylinder_vbo);
    glDeleteBuffers(1, &cylinder_ebo);

    glDeleteVertexArrays(1, &sphere_vao);
    glDeleteBuffers(1, &sphere_vbo);
    glDeleteBuffers(1, &sphere_ebo);
    glDeleteProgram(program_id);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
#endif