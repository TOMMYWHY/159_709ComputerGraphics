//
// Created by Tommy on 2020-03-06.
//
#include <iostream>
#include <fstream>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <math.h>
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




    //--------flag--------


    /*std::vector<float> flagColorList={
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
    };*/

    std::vector<float> flagVertices = {
            // 第一个三角形
            0.5f, 0.5f, 0.0f,      // 右上
            0.5f, -0.5f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   // 左下
            // 第二个三角形
            -0.5f, -0.5f, 0.0f,   // 左下
            0.5f, 0.5f, 0.0f,    // 右上
            -0.5f, 0.5f, 0.0f,   // 左上
    };

    float flagColorList []={
            .0,0.635,0.345,
            .0,0.935,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
    };

    unsigned int indices[] = {
            0, 1, 5,              // 第一个三角形
            1, 2, 5               // 第二个三角形
    };
    // VAO VBO EBO
    GLuint vao, vbo,ebo;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);//vbo 装载入 vao

    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);


    glBufferData(GL_ARRAY_BUFFER, flagVertices.size()* sizeof(float) + sizeof(flagColorList)* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, flagVertices.size()* sizeof(float), &flagVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, flagVertices.size()* sizeof(float), sizeof(flagColorList)* sizeof(float), flagColorList);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(flagVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)* sizeof(float), &indices[0], GL_STATIC_DRAW);


    //clean
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


//    glm::mat4 trans;
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 modelMat;
    modelMat = glm::rotate(modelMat,glm::radians(-55.0f),glm::vec3(1.0f,0,0));
    glm::mat4 viewMat;
    viewMat = glm::translate(viewMat,glm::vec3(0,0,-3.0f));
    glm::mat4 projMat;
    projMat = glm::perspective(glm::radians(45.0f), 800.0f/600.0f,0.1f,100.0f);
    vec = viewMat * vec;

    std::cout << vec.x << vec.y << vec.z << std::endl;

    //--engine--//
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program_id);

        glUniformMatrix4fv(glGetUniformLocation(program_id, "ModelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
        glUniformMatrix4fv(glGetUniformLocation(program_id, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(program_id, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));


        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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