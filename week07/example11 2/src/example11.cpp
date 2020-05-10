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
// Example 11 - Skybox
// --------------------------------------------------------------------------------
int main() {
	// Set Error Callback
	glfwSetErrorCallback(onError);

	// Initialise GLFW
	if (!glfwInit()) {
		// Return Error
		return 1;
	}

	// Set GLFW Window Hint - Full-Screen Antialiasing 16x
	glfwWindowHint(GLFW_SAMPLES, 16);

	// Create Window
	GLFWwindow *window = createWindow(600, 600, "Example 11 - Skybox", 3, 2);

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

	// Enable multi-sampling - Antialiasing
	glEnable(GL_MULTISAMPLE);

	// Set window callback functions
	glfwSetFramebufferSizeCallback(window, onFramebufferSize);
	glfwSetWindowCloseCallback(window, onWindowClose);

	// ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint skybox_program = loadProgram("./shader/skybox.vert.glsl",  NULL, NULL, NULL, "./shader/skybox.frag.glsl");

	// Load Texture Map
	int x, y, n;

	// // Filenames
	// const char *filenames[6] = {"images/posS.png",
	// 							"images/negS.png",
	// 							"images/negT.png",
	// 							"images/posT.png",
	// 							"images/posR.png",
	// 							"images/negR.png"};

	// Teide Volcano on Tenerife Skybox Images
	// Author: Emil Persson, aka Humus.
	// URL: http://www.humus.name
	// License: Creative Commons Attribution 3.0 Unported License.
	// Filenames
	const char *filenames[6] = {"images/posx.jpg",
								"images/negx.jpg",
								"images/negy.jpg",
								"images/posy.jpg",
								"images/posz.jpg",
								"images/negz.jpg"};

	// Load Cubemap
	GLuint texture = loadTextureCubeMap(filenames, x, y, n);

	// ----------------------------------------
	// Skybox
	// ----------------------------------------

	// Skybox Program
	glUseProgram(skybox_program);

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> skybox_buffer;
	std::vector<glm::ivec3> skybox_indexes;

	// Create Skybox
	createSkybox(skybox_buffer, skybox_indexes);

	// Vertex Array Objects (VAO)
	GLuint skybox_vao = 0;
	
	// Vertex Buffer Objects (VBO)
	GLuint skybox_vbo = 0;

	// Element Buffer Objects (EBO)
	GLuint skybox_ebo = 0;

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &skybox_vao);
	glGenBuffers(1, &skybox_vbo);
	glGenBuffers(1, &skybox_ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(skybox_vao);
	glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skybox_ebo);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, skybox_buffer.size() * sizeof(glm::vec4), skybox_buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, skybox_indexes.size() * sizeof(glm::ivec3), skybox_indexes.data(), GL_STATIC_DRAW);

	// Get Position Attribute location (must match name in shader)
	GLuint skybox_posLoc = glGetAttribLocation(skybox_program, "vert_Position");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(skybox_posLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(skybox_posLoc);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ----------------------------------------
	// Set Texture Unit
	glUseProgram(skybox_program);
	glUniform1i(glGetUniformLocation(skybox_program, "u_texture_Map"), 0);

	// ----------------------------------------
	// View Matrix
	// ----------------------------------------
	float pitch = 0.0;
	float yaw = 0.0;

	glm::mat4 viewMatrix(1.0f);
	glm::vec3 viewPosition(0.0f,  0.0f,  3.0f);
	glm::vec3 viewUp      (0.0f,  1.0f,  0.0f);
	glm::vec3 viewForward (0.0f,  0.0f,  1.0f);

	// Rotate Vectors
	glm::mat4 yawMatrix   = glm::rotate(glm::mat4(1.0f), yaw,   glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1.0f, 0.0f, 0.0f));

	// Normalise Vectors
	viewUp      = glm::normalize(yawMatrix * pitchMatrix * glm::vec4(0.0f, 1.0f,  0.0f, 0.0f));
	viewForward = glm::normalize(yawMatrix * pitchMatrix * glm::vec4(0.0f, 0.0f,  1.0f, 0.0f));

	// Calculate View Vectors
	viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(skybox_program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// ----------------------------------------
	// Projection Matrix
	// ----------------------------------------
	glm::mat4 projectionMatrix(1.0f);
	
	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.1f, 50.0f);

	// Copy Projection Matrix to Shader
	glUseProgram(skybox_program);
	glUniformMatrix4fv(glGetUniformLocation(skybox_program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	float time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to black
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update Time
		float current_time = glfwGetTime();
		float dt = current_time - time;
		time = current_time;

		// ----------------------------------------
		// Update View Matrix
		// ----------------------------------------
		if(glfwGetKey(window, GLFW_KEY_UP)) {
			// Move Forwards
			viewPosition += viewForward * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_DOWN)) {
			// Move Backwards
			viewPosition -= viewForward * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_A)) {
			// Yaw Left
			yaw += 1.0f * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_D)) {
			// Yaw Right
			yaw -= 1.0f * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_S)) {
			// Pitch Up
			pitch += 1.0f * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_W)) {
			// Pitch Down
			pitch -= 1.0f * dt;
		}

		// Calculate Pitch and Yaw
		yawMatrix   = glm::rotate(glm::mat4(1.0f), yaw,   glm::vec3(0.0f, 1.0f, 0.0f));
		pitchMatrix = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1.0f, 0.0f, 0.0f));

		// Calculate View Vectors
		viewUp      = glm::normalize(yawMatrix * pitchMatrix * glm::vec4(0.0f, 1.0f,  0.0f, 0.0f));
		viewForward = glm::normalize(yawMatrix * pitchMatrix * glm::vec4(0.0f, 0.0f,  1.0f, 0.0f));

		// Fix View Position to (0,0,0)
		// viewPosition = glm::vec3(0.0f, 0.0f, 0.0f);

		// Construct View Matrix
		viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

		// Copy View Matrix to Shader
		glUniformMatrix4fv(glGetUniformLocation(skybox_program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

		// ----------------------------------------
		// Draw Skybox
		// ----------------------------------------

		// Use Skybox Program
		glUseProgram(skybox_program);

		// Bind Vertex Array Object
		glBindVertexArray(skybox_vao);

		// Set active Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		
		// Bind Texture Map
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, skybox_indexes.size() * 3, GL_UNSIGNED_INT, NULL);

		// Set active Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Unbind Texture Map
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		// ----------------------------------------

		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Delete VAO, VBO & EBO
	glDeleteVertexArrays(1, &skybox_vao);
	glDeleteBuffers(1, &skybox_vbo);
	glDeleteBuffers(1, &skybox_ebo);

	// Delete Program
	glDeleteProgram(skybox_program);

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}


