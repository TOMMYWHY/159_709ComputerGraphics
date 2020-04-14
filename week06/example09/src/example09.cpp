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

int normal_Map_Mode = 1;

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

// Called on Key Event
void onKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
	// Check Key-Action Pairs
	if(key == GLFW_KEY_N && action == GLFW_PRESS) {
		// Cycle Normal Mapping Mode
		normal_Map_Mode = !normal_Map_Mode;
	}
}

// --------------------------------------------------------------------------------
// Example 09 - Normal Mapping
// --------------------------------------------------------------------------------
int main() {
	// Set Error Callback
	glfwSetErrorCallback(onError);

	// Initialise GLFW
	if (!glfwInit()) {
		// Return Error
		return 1;
	}

	// 4x Antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create Window
	GLFWwindow *window = createWindow(1200, 1200, "Example 09 - Normal Mapping", 3, 2);

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

	// Key Callback
	glfwSetKeyCallback(window, onKey);

	// ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_MULTISAMPLE);

	// ----------------------------------------
	// Create Object
	// ----------------------------------------

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create Textured and Tangent Cube
	createTexturedTangentCube(buffer, indexes);

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
//	 GLuint program = loadProgram("./shader/normal1.vert.glsl", NULL, NULL, NULL, "./shader/normal1.frag.glsl");
//	 GLuint program = loadProgram("./shader/normal2.vert.glsl", NULL, NULL, NULL, "./shader/normal2.frag.glsl");
	GLuint program = loadProgram("./shader/normal3.vert.glsl", NULL, NULL, NULL, "./shader/normal3.frag.glsl");

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

	// Get Texture Attribute location (must match name in shader)
	GLuint texLoc = glGetAttribLocation(program, "vert_UV");

	// Get Tangent Attribute location (must match name in shader)
	GLuint tanLoc = glGetAttribLocation(program, "vert_Tangent");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
	glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));
	glVertexAttribPointer(tanLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(12*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(norLoc);
	glEnableVertexAttribArray(texLoc);
	glEnableVertexAttribArray(tanLoc);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ----------------------------------------
	// Load Textures
	// ----------------------------------------
	int x, y, n;

	// ----------------------------------------
	// Textures License
	// ----------------------------------------
	// normal_map.png
	// License: CC BY 4.0 (https://creativecommons.org/licenses/by/4.0/)
	// Author:  Julian Herzog
	// Source:  https://commons.wikimedia.org/wiki/File:Normal_map_example_-_Map.png

	// // ----------------------------------------
	// // Load Textures
	// // ----------------------------------------
	// // Load Texture Map from file
	// GLuint texture = loadTexture2D("./images/diffuse_map.png", x, y, n);

	// // ----------------------------------------
	// // Load Normal Map from file
	// GLuint normal = loadTexture2D("./images/normal_map.png", x, y, n);

	// // ----------------------------------------
	// // Load Specular Map from file
	// GLuint specular = loadTexture2D("./images/specular_map.png", x, y, n);

	// ----------------------------------------
	// Textures License
	// ----------------------------------------
	// brick_diff.tga, brick_norm.tga, brick_spec.tga
	// License: CC BY 3.0 (https://creativecommons.org/licenses/by/3.0/)
	// Author:  JosipKladaric
	// Source:  https://opengameart.org/content/brick-wall

	// ----------------------------------------
	// Load Brick Textures
	// ----------------------------------------
	// Load Texture Map from file
	GLuint texture = loadTexture2D("./images/brick_diff.tga", x, y, n);

	// ----------------------------------------
	// Load Normal Map from file
	GLuint normal = loadTexture2D("./images/brick_norm.tga", x, y, n);

	// ----------------------------------------
	// Load Specular Map from file
	GLuint specular = loadTexture2D("./images/brick_spec.tga", x, y, n);

	// ----------------------------------------
	// Use Program
	glUseProgram(program);

	// ----------------------------------------
	// Set Texture Units
	GLuint textureMapLoc  = glGetUniformLocation(program, "u_Texture_Map");
	GLuint normalMapLoc   = glGetUniformLocation(program, "u_Normal_Map");
	GLuint specularMapLoc = glGetUniformLocation(program, "u_Specular_Map");

	glUniform1i(textureMapLoc,  0);
	glUniform1i(normalMapLoc,   1);
	glUniform1i(specularMapLoc, 2);

	// Update Normal Mapping
	glUniform1i(glGetUniformLocation(program, "u_Normal_Map_Mode"), normal_Map_Mode);

	// ----------------------------------------
	// Model Matrix
	// ----------------------------------------
	float modelThetaX =  0.0f;
	float modelThetaY =  0.0f;
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
							glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) * 
							glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

	// Copy Rotation Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	// ----------------------------------------

	// ----------------------------------------
	// View Matrix
	// ----------------------------------------
	glm::mat4 viewMatrix(1.0f);
	glm::vec3 viewPosition(0.0f,  0.0f,  4.0f);
	glm::vec3 viewUp      (0.0f,  1.0f,  0.0f);
	glm::vec3 viewForward (0.0f,  0.0f, -1.0f);

	// Normalise Vectors
	viewUp      = glm::normalize(viewUp);
	viewForward = glm::normalize(viewForward);

	// Construct View Matrix
	viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	// ----------------------------------------

	// ----------------------------------------
	// Projection Matrix
	// ----------------------------------------
	glm::mat4 projectionMatrix(1.0f);
	
	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

	// Copy Projection Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// ----------------------------------------

	float last = glfwGetTime();
	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Get elapsed time since last frame
		float time = glfwGetTime();
		float dt = time - last;
		last = time;

		// Set clear (background) colour to dark grey
		glClearColor(0.15f, 0.15f, 0.15f, 0.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use Program
		glUseProgram(program);

		// Update Normal Mapping
		glUniform1i(glGetUniformLocation(program, "u_Normal_Map_Mode"), normal_Map_Mode);

		// ----------------------------------------
		// Rotating Model Matrix
		if(glfwGetKey(window, GLFW_KEY_W)) {
			// Key - W
			modelThetaX -= 1.0f * dt;

			// Recompute Model Matrix
			modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
						  glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) * 
						  glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		if(glfwGetKey(window, GLFW_KEY_S)) {
			// Key - S
			modelThetaX += 1.0f * dt;

			// Recompute Model Matrix
			modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
						  glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) * 
						  glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		if(glfwGetKey(window, GLFW_KEY_A)) {
			// Key - A
			modelThetaY -= 1.0f * dt;

			// Recompute Model Matrix
			modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
						  glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) * 
						  glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		if(glfwGetKey(window, GLFW_KEY_D)) {
			// Key - D
			modelThetaY += 1.0f * dt;

			// Recompute Model Matrix
			modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
						  glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) * 
						  glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

			// Copy Rotation Matrix to Shader
			glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		if(glfwGetKey(window, GLFW_KEY_UP)) {
			// Move Closer
			viewPosition.z -= 1.0f * dt;

			// Construct View Matrix
			viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

			// Copy View Matrix to Shader
			glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		}

		if(glfwGetKey(window, GLFW_KEY_DOWN)) {
			// Move Away
			viewPosition.z += 1.0f * dt;

			// Construct View Matrix
			viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

			// Copy View Matrix to Shader
			glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		}
		// ----------------------------------------

		// Bind Vertex Array Object
		glBindVertexArray(vao);

		// Activate Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Bind Texture Map
		glBindTexture(GL_TEXTURE_2D, texture);

		// Activate Texture 1
		glActiveTexture(GL_TEXTURE1);

		// Bind Normal Map
		glBindTexture(GL_TEXTURE_2D, normal);

		// Activate Texture 2
		glActiveTexture(GL_TEXTURE2);

		// Bind Specular Map
		glBindTexture(GL_TEXTURE_2D, specular);

		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);

		// Activate Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Bind Texture Map
		glBindTexture(GL_TEXTURE_2D, 0);

		// Activate Texture Unit 1
		glActiveTexture(GL_TEXTURE1);

		// Unbind Normal Map
		glBindTexture(GL_TEXTURE_2D, 0);

		// Activate Texture Unit 2
		glActiveTexture(GL_TEXTURE2);

		// Unbind Specular Map
		glBindTexture(GL_TEXTURE_2D, 0);

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


