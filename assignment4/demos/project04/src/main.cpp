/*
 *  Assignment 3 , 159.709, 2020 S1
 *  Family Name: JIANG , Given Name: TAO , Student ID:20004769,
 *  OBJ Model Loader:
 *      Camera angle control: Mouse move
 *      Camera movement control: A(left); D(right); W(forward); S(back); Q(rise); E(sink);
 *      Quit: ESC
 *
 *  The model aviable to load "capsule.obj" and "muro.obj"
 *  The model params:
 *      string directory    : .obj source directory
 *      string model_name   : .obj filename
 *      GLuint shadeID      :  shader program
 *      float Scale         :  resize of the model
 *      float Pos_y         :  position of the model
 *
 *  Due to extensive kinds of obj document formats,
 *  it is currently only applicable to "capsule.obj" and "mura.obj".
 *  The model loading function will be continuously improved in the future.
 *
 * */


// System Headers
#include <iostream>
#include <fstream>
#include <cmath>

// OpenGL Headers
#if defined(_WIN32)
	#include <GL/glew.h>
	#if defined(GLEW_EGL)
		#include <GL/eglew.h>
	#elif defined(GLEW_OSMESA)
		#define GLAPI extern
		#include <GL/osmesa.h>
	#elif defined(_WIN32)
		#include <GL/wglew.h>
	#elif !defined(__APPLE__) && !defined(__HAIKU__) || defined(GLEW_APPLE_GLX)
		#include <GL/glxew.h>
	#endif

	// OpenGL Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
	#include <OpenGL/gl3.h>
	#include <OpenGL/gl3ext.h>
#elif defined(__linux__)
	// GLEW Headers
	#include <GL/glew.h>
	#include <GL/gl.h>

	// GLFW Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#endif


// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Project Headers
#include "shader.h"
#include "utils.h"
#include "geometry.h"
#include "image.h"
#include "stb_image.h"
#include <FileSystem>
#include <Camera.h>

#include <Model.h>

using namespace std;

// --------------------------------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------------------------------

// Called on Error Event
void onError(int error, const char *description);
void onWindowClose(GLFWwindow *window);
void onFramebufferSize(GLFWwindow *window, int width, int height);

float speed = 5.0f;
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::radians(15.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));
// ----- mouse function-------//
float lastX,lastY;
bool firstMouse = true;
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ----- mouse function-------//

int main() {
	// Set Error Callback
	glfwSetErrorCallback(onError);

	// Initialise GLFW
	if (!glfwInit()) {
		// Return Error
		return 1;
	}

	// Create Window
	GLFWwindow *window = createWindow(600, 600, "OBJ model loader", 3, 2);

	// Check Window
	if (window == NULL) {
		// Print Error Message
		std::cerr << "Error: create window or context failed." << std::endl;

		// Return Error
		return 1;
	}

	#if defined(_WIN32) || defined(__linux__)
		// Initialise GLEW
		if (glewInit() != GLEW_OK) {
			// Return Error
			return 1;
		}
	#endif

	// Set window callback functions
    glfwSetFramebufferSizeCallback(window, onFramebufferSize);
    glfwSetWindowCloseCallback(window, onWindowClose);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//turn off mouse

    // ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	// Load GLSL Program
	GLuint program  = loadProgram("./shader/texture.vert.glsl",  NULL, NULL, NULL, "./shader/texture.frag.glsl");

//    Model model("res/model/","capsule.obj",program , 0.5f,0);
//    Model model("res/model/","capsule1.obj",program , 0.5f,0);
    Model model("res/volcano_sleep_obj/","volcano_sleep.obj",program,1.0f,-3);

	// ----------------------------------------
	// Use Program
    glUseProgram(program);
    glm::mat4 modelMatrix(1.0f);
    glm::mat4 viewMatrix(1.0f);
    glm::mat4 projectionMatrix(1.0f);
    projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to dark grey
		glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
		// glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use Program
		glUseProgram(program);

        viewMatrix = camera->GetViewMatrix(); // camera movement

        float Rotation_theta  = 0;
        modelMatrix = glm::translate(glm::mat4(1.0f),  glm::vec3(0, model.POS_y, 0)) *
                      glm::rotate(   glm::mat4(1.0f), Rotation_theta , glm::vec3(0.0f, 1.0f, 0.0f))*
                      glm::scale(glm::mat4(1.0f),glm::vec3(model.SCALE));


        glUniformMatrix4fv(glGetUniformLocation(program,"u_Model"),1,GL_FALSE,glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program,"u_View"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program,"u_Projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));


        for (int i = 0; i < model.nodes.size(); i++) {
            model.Draw(model.nodes[i]);
        }

		// Set active Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Unbind Texture Map
		glBindTexture(GL_TEXTURE_2D, 0);

        // Swap the back and front buffers

		// Poll window events
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera->updateCameraPosition();// update camera position
    }

    // Delete VAO, VBO & EBO
    model.DeleteBuffer();

    // Delete Program
    glDeleteProgram(program);

    // Stop receiving events for the window and free resources; this must be
    // called from the main thread and should not be invoked from a callback
    glfwDestroyWindow(window);


    // Terminate GLFW
	glfwTerminate();

	return 0;
}


void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }

    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =speed;}
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -speed;}
    else{camera->speedZ = 0;}
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){camera->speedX =speed;}
    else if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){camera->speedX= -speed;}
    else{camera->speedX = 0;}
    if(glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS){camera->speedY =-speed;}
    else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS){camera->speedY= speed;}
    else{camera->speedY = 0;}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos){
    if (firstMouse == true){
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float deltaX, deltaY;
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    camera->ProcessMouseMovement(deltaX,deltaY);
}

// Called on Error Event
void onError(int error, const char *description) {
    // Print Error message
    std::cerr << "Error: " << error << " : " << description << std::endl;
}
// Called on Window Close Event
void onWindowClose(GLFWwindow *window) {
    // Nothing to do right now
    // Do not call glfwDestroyWindow from here
}
// Called on Window Size Event
void onFramebufferSize(GLFWwindow *window, int width, int height) {
    // Set-up the window/screen coordinates
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(NULL);
}
