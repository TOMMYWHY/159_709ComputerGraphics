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

// --------------------------------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------
// Example 07 - Vertex Array Objects
// --------------------------------------------------------------------------------
int main() {
	// Set Error Callback
	glfwSetErrorCallback(onError);

	// Initialise GLFW
	if (!glfwInit()) {
		// Return Error
		return 1;
	}

	// Create Window
	GLFWwindow *window = createWindow(600, 600, "Example 07 - Vertex Array Objects", 3, 2);

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

	// ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// ----------------------------------------
	// Create Object
	// ----------------------------------------

	std::vector<glm::vec4>  cube_buffer;
	std::vector<glm::ivec3> cube_indexes;
	createCubeSeparate(cube_buffer, cube_indexes);

	// ----------------------------------------
	// Create GLSL Programs
	// ----------------------------------------

	// Load GLSL Program
	GLuint phongProgram  = loadProgram( "./shader/phong.vert.glsl", NULL, NULL, NULL,  "./shader/phong.frag.glsl");



	// ----------------------------------------
	// obj1
	// ----------------------------------------
	// Vertex Array Objects (VAO)
	GLuint cube_vao1 = 0;
	// Buffer Objects (VBO)
	GLuint cube_vbo = 0;
	GLuint cube_ebo = 0;
	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &cube_vao1);
	glGenBuffers(1, &cube_vbo);
	glGenBuffers(1, &cube_ebo);
	// Bind VAO, VBO & EBO
	glBindVertexArray(cube_vao1);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo);
	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, cube_buffer.size() * sizeof(glm::vec4), cube_buffer.data(), GL_STATIC_DRAW);
	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_indexes.size() * sizeof(glm::ivec3), cube_indexes.data(), GL_STATIC_DRAW);
	// Get Position Attribute location (must match name in shader)
	GLuint colorPosLoc = glGetAttribLocation(phongProgram, "vert_Position");
	// Get Colour Attribute location (must match name in shader)
	GLuint colorColLoc = glGetAttribLocation(phongProgram, "vert_Normal");
	// Set Vertex Attribute Pointers - Separate
	glVertexAttribPointer(colorPosLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(colorColLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(16*sizeof(GLfloat)));
	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(colorPosLoc);
	glEnableVertexAttribArray(colorColLoc);
	// Unbind VAO, VBO & EBO (Unbind VAO first)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// ----------------------------------------
	// obj2
    // ----------------------------------------
    // Vertex Array Objects (VAO)
    GLuint cube_vao2 = 0;
    glGenVertexArrays(1, &cube_vao2);
    glGenBuffers(1, &cube_vbo);
    glGenBuffers(1, &cube_ebo);
    // Bind VAO, VBO & EBO
    glBindVertexArray(cube_vao2);
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo);
    // Load Vertex Data
    glBufferData(GL_ARRAY_BUFFER, cube_buffer.size() * sizeof(glm::vec4), cube_buffer.data(), GL_STATIC_DRAW);
    // Load Element Data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_indexes.size() * sizeof(glm::ivec3), cube_indexes.data(), GL_STATIC_DRAW);
    // Get Position Attribute location (must match name in shader)
    GLuint colorPosLoc2 = glGetAttribLocation(phongProgram, "vert_Position");
    // Get Colour Attribute location (must match name in shader)
    GLuint colorColLoc2 = glGetAttribLocation(phongProgram, "vert_Normal");
    // Set Vertex Attribute Pointers - Separate
    glVertexAttribPointer(colorPosLoc2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(colorColLoc2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(16*sizeof(GLfloat)));
    // Enable Vertex Attribute Arrays
    glEnableVertexAttribArray(colorPosLoc2);
    glEnableVertexAttribArray(colorColLoc2);
    // Unbind VAO, VBO & EBO (Unbind VAO first)
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//----public ---- View Matrix ------------ // function
	//----public ---- View Matrix ------------ // function
	glm::mat4 viewMatrix(1.0f);
	glm::vec3 viewPosition(0.0f,  0.0f,  5.0f);
	glm::vec3 viewUp      (0.0f,  1.0f,  0.0f);
	glm::vec3 viewForward (0.0f,  0.0f, -1.0f);
	// Normalise Vectors
	viewUp      = glm::normalize(viewUp);
	viewForward = glm::normalize(viewForward);
	// Construct View Matrix
	viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
	// Projection Matrix
	glm::mat4 projectionMatrix(1.0f);
	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 10.0f);

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to dark grey
		glClearColor(0.15f, 0.15f, 0.15f, 0.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use Colour Program
        glUseProgram(phongProgram);

		// ----------------------------------------
		// Orbiting - View Matrix
		viewPosition.x = sin(glfwGetTime()) * 8.0f;
		viewPosition.z = cos(glfwGetTime()) * 8.0f;
/*        viewPosition.x =  2.0f;
        viewPosition.z = 2.0f;*/
		// Look towards origin
		viewForward = -viewPosition;

		// Normalise Vectors
		viewUp      = glm::normalize(viewUp);
		viewForward = glm::normalize(viewForward);

		// Construct View Matrix
		viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
		// ----------------------------------------

		// ----------------------------------------
		// obj1
		// ----------------------------------------

        glm::mat4 cubeModelMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f));
        cubeModelMatrix1 = glm::rotate(cubeModelMatrix1, (float)glfwGetTime()*2, glm::vec3(1.0f, 1.0f, 0.0f));
        cubeModelMatrix1 = glm::scale(cubeModelMatrix1, glm::vec3(.5f,.5f,.5f));
        // Copy Model Matrix to Shader
        glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_Model"),      1, GL_FALSE, glm::value_ptr(cubeModelMatrix1));
        // Copy View Matrix to Shader
        glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_View"),       1, GL_FALSE, glm::value_ptr(viewMatrix));
        // Copy Projection Matrix to Shader
        glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glBindVertexArray(cube_vao1);
		// Draw Tetrahedron
		glDrawElements(GL_TRIANGLES, cube_indexes.size() * 3, GL_UNSIGNED_INT, NULL);

		// Unbind Tetrahedron Vertex Array Object
		glBindVertexArray(0);
		// ----------------------------------------

		// ----------------------------------------
		// obj2
		// ----------------------------------------
        glm::mat4 cubeModelMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
        cubeModelMatrix2 = glm::rotate(cubeModelMatrix2, (float)glfwGetTime()*5, glm::vec3(0.0f, 1.0f, 0.0f));
        cubeModelMatrix2 = glm::scale(cubeModelMatrix2, glm::vec3(.8f,.8f,.8f));
        // Copy Model Matrix to Shader
        glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_Model"),      1, GL_FALSE, glm::value_ptr(cubeModelMatrix2));
        // Copy View Matrix to Shader
        glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_View"),       1, GL_FALSE, glm::value_ptr(viewMatrix));
        // Copy Projection Matrix to Shader
        glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glBindVertexArray(cube_vao2);
        // Draw Tetrahedron
        glDrawElements(GL_TRIANGLES, cube_indexes.size() * 3, GL_UNSIGNED_INT, NULL);

        // Unbind Tetrahedron Vertex Array Object
        glBindVertexArray(0);


		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Delete VAO, VBO & EBO
	glDeleteVertexArrays(1, &cube_vao1);
	glDeleteVertexArrays(1, &cube_vao2);
	glDeleteBuffers(1, &cube_vbo);
	glDeleteBuffers(1, &cube_ebo);

/*	glDeleteVertexArrays(1, &cube_vao1);
	glDeleteBuffers(1, &cube_vbo);
	glDeleteBuffers(1, &cube_ebo);*/

	// Delete Programs
//	glDeleteProgram(phongProgram2);
	glDeleteProgram(phongProgram);

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}


