//
// Created by Tommy on 2020-03-06.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

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

    // 生成球的顶点
    const int Y_SEGMENTS = 50;
    const int X_SEGMENTS = 50;
    const float radius = 0.07;
    const GLfloat  PI = 3.14159265358979323846f;
    std::vector<float> sphereVertices;
    std::vector<int> sphereIndices;
    std::vector<float> buffer_all;
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
            sphereVertices.push_back(yPos*radius);
            sphereVertices.push_back(zPos*radius);
        }
    }

    // 生成球的Indices
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

//    std::cout<<"testing"<<sphereVertices.size()<<std::endl;
    std::vector<float> sphereFragColor;
    int sphereVertices_amount = sphereVertices.size();
    std::cout<<sphereVertices_amount<<endl ;
    for(int i=0;i<sphereVertices.size();i++)
    {
//        sphereFragColor[i] = 0.9f;
        sphereFragColor.push_back(0.3f);
//        std::cout<<sphereFragColor[i]<<"," << std::endl;
    }
    sphereVertices.insert(sphereVertices.end(),sphereFragColor.begin(),sphereFragColor.end());

    for(int i=0;i<sphereVertices.size();i++)
    {
        std::cout<<sphereVertices[i]<<" ; "  ;
    }

    std::cout<<sphereVertices.size()<<endl ;
    // Triangle Vertexes (and colours)



    // VAO VBO EBO
    GLuint vao, vbo,ebo;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);//vbo 装载入 vao

    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//    glBufferData(GL_ARRAY_BUFFER,  sizeof(buffer), buffer, GL_STATIC_DRAW);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    // Load Vertex Data
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);
    // Load Element Data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

//    GLuint posLoc = glGetAttribLocation(program_id, "vert_Position");
//    GLuint colLoc = glGetAttribLocation(program_id,"vert_Colour");
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(sphereVertices_amount,3,GL_FLOAT,GL_FALSE,3* sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
//    glEnableVertexAttribArray(posLoc);
//    glEnableVertexAttribArray(colLoc);

//    glEnableVertexAttribArray(0);
// 颜色属性
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
//    glEnableVertexAttribArray(1);
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
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glDrawElements(GL_TRIANGLES, X_SEGMENTS*Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);


        unsigned int transformLoc = glGetUniformLocation(program_id, "transform");



        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);


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