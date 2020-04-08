// System Headers
#include <iostream>
#include <fstream>
#include <cmath>

// OpenGL Headers
#if defined(_WIN32)
	// OpenGL Headers
	#include <GL/glew.h>
	#include <GL/wglew.h>

	// GLFW Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
	// GLFW Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>

	// OpenGL Headers
	#include <OpenGL/gl3.h>
#elif defined(__linux__)
	// GLEW Headers
	#include <GL/glew.h>
	#include <GL/gl.h>

	// GLFW Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#endif

// GLM Headers
#define GLM_ENABLE_EXPERIMENTAL
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
// Example 06 - Lighting & Shading
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
	GLFWwindow *window = createWindow(600, 600, "Example 06 - Lighting & Shading", 4, 0);

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

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create Cube
	 createCube(buffer, indexes);

	// // Create Tetrahedron
	// createTetrahedron(buffer, indexes);

	// // Create Torus
//	createTorus(buffer, indexes, 2.0f, 0.9f, 20, 20);

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint phongProgram  = loadProgram("./shader/phong.vert.glsl",  NULL, NULL, NULL, "./shader/phong.frag.glsl");
	GLuint goraudProgram = loadProgram("./shader/goraud.vert.glsl", NULL, NULL, NULL, "./shader/goraud.frag.glsl");

	// GLuint program = goraudProgram;
	GLuint program = phongProgram;

	// Use Program
	glUseProgram(program);

	// Vertex Array Objects (VAO)
	GLuint vao = 0;
	
	// Vertex Buffer Objects (VBO)
	GLuint vbo = 0;

	// Element Buffer Objects (EBO)
	GLuint ebo = 0;

	// ----------------------------------------
	// Triangle
	// ----------------------------------------

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(vao);
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

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(norLoc);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ----------------------------------------
	// Model Matrix
	glm::mat4 modelMatrix(1.0f);
	float modelThetaX = 0.8f;
	float modelThetaY = 0.0f;

	// Calculate Model Matrix
	modelMatrix = glm::rotate(modelMatrix, modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

	// Get Model Matrix location
	GLint modelLoc = glGetUniformLocation(program, "u_Model");

	// Copy Rotation Matrix to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	// ----------------------------------------

	// ----------------------------------------
	// View Matrix
	glm::mat4 viewMatrix(1.0f);
	glm::vec3 viewPosition(0.0f,  0.0f,  2.0f);
	glm::vec3 viewUp      (0.0f,  1.0f,  0.0f);
	glm::vec3 viewForward (0.0f,  0.0f, -1.0f);

	// Normalise Vectors
	viewUp      = glm::normalize(viewUp);
	viewForward = glm::normalize(viewForward);

	// Construct View Matrix
	viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

	// Get View Matrix location
	GLint viewLoc = glGetUniformLocation(program, "u_View");

	// Copy View Matrix to Shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	// ----------------------------------------

	// ----------------------------------------
	// Projection Matrix
	glm::mat4 projectionMatrix(1.0f);
	
	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 10.0f);

	// Get Projection Matrix location
	GLint projectionLoc = glGetUniformLocation(program, "u_Projection");

	// Copy Projection Matrix to Shader
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// ----------------------------------------

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

		// Use Program
		glUseProgram(program);

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

		// Copy View Matrix to Shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		// ----------------------------------------

		// ----------------------------------------		
		// Input/Output - Model Matrix
		// ----------------------------------------
		// Check W Key
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			// Rotate Model around X axis
			modelThetaX += 0.001f;

			// Calculate Model Matrix
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::rotate(modelMatrix, modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		// Check S Key
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			// Rotate Model around X axis
			modelThetaX -= 0.001f;

			// Calculate Model Matrix
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::rotate(modelMatrix, modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		// Check A Key
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			// Rotate Model around Y axis
			modelThetaY += 0.001f;

			// Calculate Model Matrix
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::rotate(modelMatrix, modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		// Check D Key
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			// Rotate Model around Y axis
			modelThetaY -= 0.001f;

			// Calculate Model Matrix
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::rotate(modelMatrix, modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}
		// ----------------------------------------

		// Bind Vertex Array Object
		glBindVertexArray(vao);

		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);

		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
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


