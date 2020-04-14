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

	// Vertex and Index buffers (tetrahedron)
	std::vector<glm::vec4>  tetrahedron_buffer;
	std::vector<glm::ivec3> tetrahedron_indexes;

	// Vertex and Index buffers (cube)
	std::vector<glm::vec4>  cube_buffer;
	std::vector<glm::ivec3> cube_indexes;

	// // Create Cube - (Interleaved)
	// createCubeInterleaved(cube_buffer, cube_indexes);

	// Create Cube - (Separate)
	createCubeSeparate(cube_buffer, cube_indexes);

	// // Create Tetrahedron - (Interleaved)
	// createTetrahedronInterleaved(tetrahedron_buffer, tetrahedron_indexes);

	// Create Tetrahedron - (Separate)
	createTetrahedronSeparate(tetrahedron_buffer, tetrahedron_indexes);

	// ----------------------------------------
	// Create GLSL Programs
	// ----------------------------------------

	// Load GLSL Program
	GLuint colourProgram = loadProgram("./shader/colour.vert.glsl", NULL, NULL, NULL, "./shader/colour.frag.glsl");
	GLuint phongProgram  = loadProgram( "./shader/phong.vert.glsl", NULL, NULL, NULL,  "./shader/phong.frag.glsl");

	// ----------------------------------------
	// Configure Tetrahedron
	// ----------------------------------------
	// Vertex Array Objects (VAO)
	GLuint tetrahedron_vao = 0;
	
	// Buffer Objects (VBO)
	GLuint tetrahedron_vbo = 0;
	GLuint tetrahedron_ebo = 0;

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &tetrahedron_vao);
	glGenBuffers(1, &tetrahedron_vbo);
	glGenBuffers(1, &tetrahedron_ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(tetrahedron_vao);
	glBindBuffer(GL_ARRAY_BUFFER, tetrahedron_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tetrahedron_ebo);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, tetrahedron_buffer.size() * sizeof(glm::vec4), tetrahedron_buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tetrahedron_indexes.size() * sizeof(glm::ivec3), tetrahedron_indexes.data(), GL_STATIC_DRAW);

	// Get Position Attribute location (must match name in shader)
	GLuint colorPosLoc = glGetAttribLocation(colourProgram, "vert_Position");

	// Get Colour Attribute location (must match name in shader)
	GLuint colorColLoc = glGetAttribLocation(colourProgram, "vert_Colour");

	// // Set Vertex Attribute Pointers - Interleaved
	// glVertexAttribPointer(colorPosLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	// glVertexAttribPointer(colorColLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4*sizeof(GLfloat)));

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
	// Configure Cube
	// ----------------------------------------
	// Vertex Array Objects (VAO)
	GLuint cube_vao = 0;
	
	// Buffer Objects (VBO)
	GLuint cube_vbo = 0;
	GLuint cube_ebo = 0;

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &cube_vao);
	glGenBuffers(1, &cube_vbo);
	glGenBuffers(1, &cube_ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, cube_buffer.size() * sizeof(glm::vec4), cube_buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_indexes.size() * sizeof(glm::ivec3), cube_indexes.data(), GL_STATIC_DRAW);

	// Get Position Attribute location (must match name in shader)
	GLuint phongPosLoc = glGetAttribLocation(phongProgram, "vert_Position");

	// Get Normal Attribute location (must match name in shader)
	GLuint phongNorLoc = glGetAttribLocation(phongProgram, "vert_Normal");

	// // Set Vertex Attribute Pointers - Interleaved
	// glVertexAttribPointer(phongPosLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	// glVertexAttribPointer(phongNorLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4*sizeof(GLfloat)));

	// Set Vertex Attribute Pointers - Separate
	glVertexAttribPointer(phongPosLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(phongNorLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(96*sizeof(GLfloat)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(phongPosLoc);
	glEnableVertexAttribArray(phongNorLoc);

	// Unbind VAO, VBO & EBO (Unbind VAO first)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// ----------------------------------------
	// Create Transforms
	// ----------------------------------------

	// ----------------------------------------
	// Tetrahedron - Model Matrix
	glm::mat4 tetrahedronModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	// ----------------------------------------

	// ----------------------------------------
	// Cube - Model Matrix
	glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// ----------------------------------------

	// ----------------------------------------
	// View Matrix
	glm::mat4 viewMatrix(1.0f);
	glm::vec3 viewPosition(0.0f,  0.0f,  5.0f);
	glm::vec3 viewUp      (0.0f,  1.0f,  0.0f);
	glm::vec3 viewForward (0.0f,  0.0f, -1.0f);

	// Normalise Vectors
	viewUp      = glm::normalize(viewUp);
	viewForward = glm::normalize(viewForward);

	// Construct View Matrix
	viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
	// ----------------------------------------

	// ----------------------------------------
	// Projection Matrix
	glm::mat4 projectionMatrix(1.0f);
	
	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 10.0f);
	// ----------------------------------------


	// ----------------------------------------
	// Copy to Shader Programs
	// ----------------------------------------

	// ----------------------------------------
	// Use Colour Program
	glUseProgram(colourProgram);

	// Copy Model Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(colourProgram, "u_Model"),      1, GL_FALSE, glm::value_ptr(tetrahedronModelMatrix));

	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(colourProgram, "u_View"),       1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Copy Projection Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(colourProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// ----------------------------------------
	// Copy to Phong Program
	glUseProgram(phongProgram);

	// Copy Model Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_Model"),      1, GL_FALSE, glm::value_ptr(cubeModelMatrix));

	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_View"),       1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Copy Projection Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));


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


		// ----------------------------------------
		// Orbiting - View Matrix
		viewPosition.x = sin(glfwGetTime()) * 5.0f;
		viewPosition.z = cos(glfwGetTime()) * 5.0f;

		// Look towards origin
		viewForward = -viewPosition;

		// Normalise Vectors
		viewUp      = glm::normalize(viewUp);
		viewForward = glm::normalize(viewForward);

		// Construct View Matrix
		viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
		// ----------------------------------------

		// ----------------------------------------
		// Draw Tetrahedron
		// ----------------------------------------

		// Use Colour Program
		glUseProgram(colourProgram);

		// Copy View Matrix to Shader
		glUniformMatrix4fv(glGetUniformLocation(colourProgram, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

		// Bind Tetrahedron Vertex Array Object
		glBindVertexArray(tetrahedron_vao);

		// Draw Tetrahedron
		glDrawElements(GL_TRIANGLES, tetrahedron_indexes.size() * 3, GL_UNSIGNED_INT, NULL);

		// Unbind Tetrahedron Vertex Array Object
		glBindVertexArray(0);
		// ----------------------------------------

		// ----------------------------------------
		// Draw Cube
		// ----------------------------------------

		// Use Phong Program
		glUseProgram(phongProgram);

		// Copy View Matrix to Shader
		glUniformMatrix4fv(glGetUniformLocation(phongProgram, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

		// Bind Cube Vertex Array Object
		glBindVertexArray(cube_vao);

		// Draw Cube
		glDrawElements(GL_TRIANGLES, cube_indexes.size() * 3, GL_UNSIGNED_INT, NULL);

		// Unbind Cube Vertex Array Object
		glBindVertexArray(0);
		// ----------------------------------------


		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Delete VAO, VBO & EBO
	glDeleteVertexArrays(1, &tetrahedron_vao);
	glDeleteBuffers(1, &tetrahedron_vbo);
	glDeleteBuffers(1, &tetrahedron_ebo);

	glDeleteVertexArrays(1, &cube_vao);
	glDeleteBuffers(1, &cube_vbo);
	glDeleteBuffers(1, &cube_ebo);

	// Delete Programs
	glDeleteProgram(colourProgram);
	glDeleteProgram(phongProgram);

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}


