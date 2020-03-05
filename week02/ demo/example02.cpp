#include <iostream>
#include <fstream>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

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
    // Check shaders for errors
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


/*
 * shader
 */


int main(){
    glfwSetErrorCallback(onError);

    glfwInit();
    if(!glfwInit()){
        cout << "Failed to initialize GLFW!\n";
        return 1;
    }
    GLFWwindow* window = create_window(500,400,"example2...");
    if (window == NULL) {
        // Print Error Message
        cerr << "Error: create window or context failed." << endl;
        // Return Error
        return 1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);


    // v shader
    GLuint v_shader_id = load_shader(GL_VERTEX_SHADER,"shaders/vert.glsl");
    // f shader
    GLuint f_shader_id = load_shader(GL_FRAGMENT_SHADER,"shaders/frag.glsl");
    // program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id,v_shader_id);
    glAttachShader(program_id, f_shader_id);
    glLinkProgram(program_id);
    glUseProgram(program_id);
    if(program_id == 0) {
        // Print Error Message
        cerr << "Error: could not load GLSL program" << endl;
        // Return Error
        return 1;
    }


//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);

    // OpenGL Winding Order
//     glFrontFace(GL_CCW);	// Counter-Clockwise
//     glFrontFace(GL_CW);	// Clockwise

    /*GLfloat buffer[9];
    buffer[0] =  1.0f; buffer[1] =  0.577f; buffer[2] =  0.0f;
    buffer[3] =  0.5f; buffer[4] = -0.289f; buffer[5] =  0.0f;
    buffer[6] = -0.5f; buffer[7] = -0.789f; buffer[8] =  0.0f;*/

   /* GLfloat buffer[12];
	buffer[0] =  0.5f; buffer[1]  =  0.5f; buffer[2]  =  0.0f;
	buffer[3] = -0.5f; buffer[4]  =  0.5f; buffer[5]  =  0.0f;
	buffer[6] =  0.5f; buffer[7]  = -0.5f; buffer[8]  =  0.0f;
	buffer[9] = -0.5f; buffer[10] = -0.5f; buffer[11] =  0.0f;*/


    // Triangle Vertexes (and colours)
    GLfloat buffer[18];

    buffer[0]  =  0.0f; buffer[1]  =  0.577f; buffer[2]  =  0.0f;
    buffer[3]  =  1.0f; buffer[4]  =  0.0f;   buffer[5]  =  0.0f;

    buffer[6]  =  0.5f; buffer[7]  = -0.289f; buffer[8]  =  0.0f;
    buffer[9]  =  0.0f; buffer[10] =  1.0f;   buffer[11] =  0.0f;

    buffer[12] = -0.5f; buffer[13] = -0.289f; buffer[14] =  0.0f;
    buffer[15] =  0.0f; buffer[16] =  0.0f;   buffer[17] =  1.0f;


    //===VAO VBO ===//
    GLuint vao, vbo;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);//vbo 装载入 vao

    // buffer[] 装载入 vbo
//    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), buffer, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), buffer, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER,  sizeof(buffer), buffer, GL_STATIC_DRAW);


//就是告诉OpenGl，编号为 0 的opengl属性 使用当前绑定在GL_ARRAY_BUFFER​的VBO。
    /*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);*/
    /*GLuint posLoc = glGetAttribLocation(program_id, "vert_Position");
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(posLoc);*/

    GLuint posLoc = glGetAttribLocation(program_id, "vert_Position");
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(posLoc);
    GLuint colLoc = glGetAttribLocation(program_id,"vert_Colour");
    glVertexAttribPointer(colLoc,3,GL_FLOAT,GL_FALSE,6* sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(colLoc);








    //=================//engine//=================//
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        glUseProgram(program_id);

    // Draw Elements (Triangles)
//		 glDrawArrays(GL_POINTS, 0, 3);
//         glDrawArrays(GL_LINES, 0, 3);
//         glDrawArrays(GL_LINE_STRIP, 0, 3);
//         glDrawArrays(GL_LINE_LOOP, 0, 3);
//        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw Elements (Square)
//         glDrawArrays(GL_POINTS, 0, 4);
//         glDrawArrays(GL_LINES, 0, 4);
//		glDrawArrays(GL_LINE_STRIP, 0, 4);
        // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        /*
         * testing....
         */
//        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);                                          // 绘制三角形

//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}