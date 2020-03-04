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
 * shader
 */

const float triangle[] = {
//     ---- 位置 ----
        -0.5f, -0.5f, 0.0f,   // 左下
        0.5f, -0.5f, 0.0f,   // 右下
        0.0f,  0.5f, 0.0f    // 正上
};

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


    /*
     * shader
     */
    // reading shader file
   /* const char* filename = "vert.glsl";

    ifstream input(filename);
    //fstream还有和open()一样的构造函数
    *//*ifstream input;
    input.open(filename);*//*
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
    cout <<"shader:"<< data <<endl;*/



    const char *vertex_shader_source =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"           // 位置变量的属性位置值为0
//            "in vec3 vert_Position;\n"           // 位置变量的属性位置值为0
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos, 1.0);\n"
            "}\n\0";
    const char *fragment_shader_source =
            "#version 330 core\n"
            "out vec4 FragColor;\n"                           // 输出的颜色向量
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";


    // v shader
    GLuint v_shader_id = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(v_shader_id,1,&data,NULL);
    glShaderSource(v_shader_id,1,&vertex_shader_source,NULL);
    glCompileShader(v_shader_id);
    // check v shader

    //fragment temp....
    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    // program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id,v_shader_id);
    glAttachShader(program_id, fragment_shader);

    glLinkProgram(program_id);
    glUseProgram(program_id);
    if(program_id == 0) {
        // Print Error Message
        std::cerr << "Error: could not load GLSL program" << std::endl;

        // Return Error
        return 1;
    }

    // check link


    /*
    * buffers
    */
    /* mac 不需要 glew
     * if (glewInit() != GLEW_OK) {
        // Return Error
        return 1;
    }*/
//     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLfloat buffer[9];
    buffer[0] =  0.0f; buffer[1] =  0.577f; buffer[2] =  0.5f;
    buffer[3] =  0.5f; buffer[4] = -0.289f; buffer[5] =  0.5f;
    buffer[6] = -0.5f; buffer[7] = -0.289f; buffer[8] =  0.5f;


    //VAO VBO //
    GLuint vao, vbo;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);//vbo 装载入 vao

    // buffer 装载入 vbo
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), buffer, GL_STATIC_DRAW);

    // todo
    //  program id  与 shader 中的 vert_Position 建立对应关系
    /*GLuint posLoc = glGetAttribLocation(program_id, "vert_Position");
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(posLoc);*/

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);









    //=================//engine//=================//
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        glUseProgram(program_id);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}