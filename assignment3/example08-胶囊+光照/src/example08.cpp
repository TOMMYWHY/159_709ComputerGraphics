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
#include <ObjModel.h>

using namespace std;

// --------------------------------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------------------------------

// Called on Error Event
void onError(int error, const char *description);
void onWindowClose(GLFWwindow *window);
void onFramebufferSize(GLFWwindow *window, int width, int height);

// --------------------------------------------------------------------------------
// Example 07 - Texture Mapping
// --------------------------------------------------------------------------------



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
	GLFWwindow *window = createWindow(600, 600, "Example 08 - Texturing", 3, 2);

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

	// ----------------------------------------
	// Create Object
	// ----------------------------------------

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create Textured Cube
//	createTexturedCube(buffer, indexes);
    createSphere(buffer, indexes,0.8f,50,50);

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint program  = loadProgram("./shader/texture.vert.glsl",  NULL, NULL, NULL, "./shader/texture.frag.glsl");

	//todo
    ObjModel model;
    model.Init("res/model/muro.obj");
//    model.Init("res/model/capsule.obj");

//    model.loadMtlFile("res/model/capsule.mtl");


    // Vertex Array Objects (VAO)
	GLuint vao = 0;
	
	// Vertex Buffer Objects (VBO)
	GLuint vbo = 0;

	// Element Buffer Objects (EBO)
	GLuint ebo = 0;

	// ----------------------------------------
	// Load Texture Map from file
	int x, y, n;
//    GLuint texture = loadTexture2D("./res/model/capsule0.jpg", x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
//    GLuint texture = loadTexture2D("./images/earth_nightmap.jpg", x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
//    GLuint texture_specular = loadTexture2D("./images/earthspec1k.jpg", x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);


	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(vao);
/*
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

	// Get Position Attribute location (must match name in shader)
	GLuint posLoc = glGetAttribLocation(program, "vert_Position");

	// Get Normal Attribute location (must match name in shader)
	GLuint norLoc = glGetAttribLocation(program, "vert_Normal");

	// Get Texture Attribute location (must match name in shader)
	GLuint texLoc = glGetAttribLocation(program, "vert_UV");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
	glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(norLoc);
	glEnableVertexAttribArray(texLoc);
*/
        //todo
    GLuint posLoc = glGetAttribLocation(program, "vert_Position");
    GLuint norLoc = glGetAttribLocation(program, "vert_Normal");
    GLuint texLoc = glGetAttribLocation(program, "vert_UV");
    model.Bind(posLoc,texLoc,norLoc);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

//        float Rotation_theta  = (float)(glfwGetTime()* 0.5f);
        float Rotation_theta  = 0;
        modelMatrix = glm::translate(glm::mat4(1.0f),  glm::vec3(0, 0, 0)) *
                      glm::rotate(   glm::mat4(1.0f), Rotation_theta , glm::vec3(0.0f, 1.0f, 0.0f))*
                      glm::scale(glm::mat4(1.0f),glm::vec3(0.05f));


        glUniformMatrix4fv(glGetUniformLocation(program,"u_Model"),1,GL_FALSE,glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program,"u_View"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program,"u_Projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));


       /* glActiveTexture(GL_TEXTURE0 );// 0 texture
        glBindTexture(GL_TEXTURE_2D,texture);
        glActiveTexture(GL_TEXTURE1 );// 1  texture
        glBindTexture(GL_TEXTURE_2D,texture_specular);

        glUniform1i(glGetUniformLocation(program, "u_texture_Map"), 0); // texture
        glUniform1i(glGetUniformLocation(program, "material_specular"), 1); // texture*/
        // ----------------------------------------

		// Bind Vertex Array Object
		glBindVertexArray(vao);


		// Draw Elements (Triangles)
		//todo
        model.Draw(program);

//		glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);

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
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

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
    float speed = 10.0f;
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =speed;}
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -speed;}
    else{camera->speedZ = 0;}
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){camera->speedX =speed;}
    else if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){camera->speedX= -speed;}
    else{camera->speedX = 0;}
    // Q下沉 E上浮
    if(glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS){camera->speedY =-speed;}
    else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS){camera->speedY= speed;}
    else{camera->speedY = 0;}

    /*
     if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =1.0f;}
     else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -1.0f;}
     else{camera->speedZ = 0;}*/

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
//    cout<<"xpos:" <<xPos<< ", ypos:"<< yPos<<endl;
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
