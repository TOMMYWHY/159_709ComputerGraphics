#include <iostream>
#include <fstream>

#include <GLFW/glfw3.h>
using namespace std;

// create window
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
    return window;
}

int main(){
//    glfwInit();
    if(!glfwInit()){
        cout << "Failed to initialize GLFW!\n";
        return 1;
    }
    GLFWwindow* window = create_window(500,400,"testing...");

    glfwMakeContextCurrent(window);


    //engine
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();
    cout <<"testing..." <<endl;
    return 0;
}