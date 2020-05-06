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
#include "camera.h"

// Camera
Camera *camera;

// Tessellation Parameters
float tessLevelInner1 = 1.0f;
float tessLevelInner2 = 1.0f;

float tessLevelOuter1 = 1.0f;
float tessLevelOuter2 = 1.0f;
float tessLevelOuter3 = 1.0f;
float tessLevelOuter4 = 1.0f;

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
// Keyboard Input
// --------------------------------------------------------------------------------
void onKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
	// Max Tessellation Level
	float min = 1.0f;
	float max = 64.0f;
	float inc = 1.0f;

	// Check Input Key - 1
	if((key == GLFW_KEY_1) && (action == GLFW_PRESS || action == GLFW_REPEAT) && !(mods & GLFW_MOD_CONTROL)) {
		// Check Shift Key
		if((mods & GLFW_MOD_SHIFT)) {
			// Increase Outer Tessellation
			tessLevelOuter1 = (tessLevelOuter1 + inc < max) ? tessLevelOuter1 + inc : max;
		} else {
			// Decrease Outer Tessellation
			tessLevelOuter1 = (tessLevelOuter1 - inc > min)  ? tessLevelOuter1 - inc : min;
		}
		std::cout << "Outer1: " << tessLevelOuter1 << std::endl;
	}
	// Check Input Key - 2
	if((key == GLFW_KEY_2) && (action == GLFW_PRESS || action == GLFW_REPEAT) && !(mods & GLFW_MOD_CONTROL)) {
		// Check Shift Key
		if((mods & GLFW_MOD_SHIFT)) {
			// Increase Outer Tessellation
			tessLevelOuter2 = (tessLevelOuter2 + inc < max) ? tessLevelOuter2 + inc : max;
		} else {
			// Decrease Outer Tessellation
			tessLevelOuter2 = (tessLevelOuter2 - inc > min)  ? tessLevelOuter2 - inc : min;
		}
		std::cout << "Outer2: " << tessLevelOuter2 << std::endl;
	}
	// Check Input Key - 3
	if((key == GLFW_KEY_3) && (action == GLFW_PRESS || action == GLFW_REPEAT) && !(mods & GLFW_MOD_CONTROL)) {
		// Check Shift Key
		if((mods & GLFW_MOD_SHIFT)) {
			// Increase Outer Tessellation
			tessLevelOuter3 = (tessLevelOuter3 + inc < max) ? tessLevelOuter3 + inc : max;
		} else {
			// Decrease Outer Tessellation
			tessLevelOuter3 = (tessLevelOuter3 - inc > min)  ? tessLevelOuter3 - inc : min;
		}
		std::cout << "Outer3: " << tessLevelOuter3 << std::endl;
	}
	// Check Input Key - 4
	if((key == GLFW_KEY_4) && (action == GLFW_PRESS || action == GLFW_REPEAT) && !(mods & GLFW_MOD_CONTROL)) {
		// Check Shift Key
		if((mods & GLFW_MOD_SHIFT)) {
			// Increase Outer Tessellation
			tessLevelOuter4 = (tessLevelOuter4 + inc < max) ? tessLevelOuter4 + inc : max;
		} else {
			// Decrease Outer Tessellation
			tessLevelOuter4 = (tessLevelOuter4 - inc > min)  ? tessLevelOuter4 - inc : min;
		}
		std::cout << "Outer4: " << tessLevelOuter4 << std::endl;
	}




	// Check Input Key - 1
	if((key == GLFW_KEY_1) && (action == GLFW_PRESS || action == GLFW_REPEAT) && (mods & GLFW_MOD_CONTROL)) {
		// Check Shift Key
		if(mods & GLFW_MOD_SHIFT) {
			// Increase Inner Tessellation
			tessLevelInner1 = (tessLevelInner1 + inc < max) ? tessLevelInner1 + inc : max;
		} else {
			// Decrease Inner Tessellation
			tessLevelInner1 = (tessLevelInner1 - inc > min)  ? tessLevelInner1 - inc : min;
		}
		std::cout << "Inner1: " << tessLevelInner1 << std::endl;
	}
	// Check Input Key - 2
	if((key == GLFW_KEY_2) && (action == GLFW_PRESS || action == GLFW_REPEAT) && (mods & GLFW_MOD_CONTROL)) {
		// Check Shift Key
		if(mods & GLFW_MOD_SHIFT) {
			// Increase Inner Tessellation
			tessLevelInner2 = (tessLevelInner2 + inc < max) ? tessLevelInner2 + inc : max;
		} else {
			// Decrease Inner Tessellation
			tessLevelInner2 = (tessLevelInner2 - inc > min)  ? tessLevelInner2 - inc : min;
		}
		std::cout << "Inner2: " << tessLevelInner2 << std::endl;
	}

	// Check Input Key - I
	if((key == GLFW_KEY_I) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		// Check Shift Key
		if(mods & GLFW_MOD_SHIFT) {
			// Increase Inner Tessellation
			tessLevelInner1 = tessLevelInner2 = (tessLevelInner1 + inc < max) ? tessLevelInner1 + inc : max;

		} else {
			// Decrease Inner Tessellation
			tessLevelInner1 = tessLevelInner2 = (tessLevelInner1 - inc > min)  ? tessLevelInner1 - inc : min;
		}
		std::cout << "Inner: " << tessLevelInner1 << std::endl;
	}
	// Check Input Key - O
	if((key == GLFW_KEY_O) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		// Check Shift Key
		if((mods & GLFW_MOD_SHIFT)) {
			// Increase Outer Tessellation
			tessLevelOuter1 = tessLevelOuter2 = tessLevelOuter3 = tessLevelOuter4 = (tessLevelOuter1 + inc < max) ? tessLevelOuter1 + inc : max;
		} else {
			// Decrease Outer Tessellation
			tessLevelOuter1 = tessLevelOuter2 = tessLevelOuter3 = tessLevelOuter4 = (tessLevelOuter1 - inc > min)  ? tessLevelOuter1 - inc : min;
		}
		std::cout << "Outer: " << tessLevelOuter1 << std::endl;
	}
}

// --------------------------------------------------------------------------------
// Mouse Input
// --------------------------------------------------------------------------------
void onMouseButton(GLFWwindow *window, int button, int action, int mods) {
	// Update Camera
	camera->onMouseButton(window, button, action, mods);
}

void onCursorPosition(GLFWwindow *window, double x, double y) {
	// Update Camera
	camera->onCursorPosition(window, x, y);
}

// --------------------------------------------------------------------------------
// Example 15 - Tessellation
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
	GLFWwindow *window = createWindow(600, 600, "Example 15 - Tessellation", 3, 2);

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

	// Set mouse input callback functions
	glfwSetMouseButtonCallback(window, onMouseButton);
	glfwSetCursorPosCallback(window, onCursorPosition);

	// Set keyboard input callback functions
	glfwSetKeyCallback(window, onKey);

	// ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ----------------------------------------
	// Camera
	// ----------------------------------------
	camera = new GimbalFreeLookCamera(window);

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint program = loadProgram("./shader/tessellation.vert.glsl",
								 "./shader/tessellation.ctrl.glsl",
								 "./shader/tessellation.eval.glsl",
								 NULL,
								 "./shader/tessellation.frag.glsl");

	// Use Program
	glUseProgram(program);

	// ----------------------------------------
	// Vertex Array Object
	// ----------------------------------------
	// Vertex Array Objects (VAO)
	GLuint vao = 0;
	
	// Vertex Buffer Objects (VBO)
	GLuint vbo = 0;

	// Element Buffer Objects (EBO)
	GLuint ebo = 0;

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Get Position Attribute location (must match name in shader)
	GLuint posLoc = glGetAttribLocation(program, "vert_Position");

	// Get Normal Attribute location (must match name in shader)
	GLuint norLoc = glGetAttribLocation(program, "vert_Colour");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(norLoc);

	// ----------------------------------------
	// Object - Triangle
	// ----------------------------------------

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create Triangle
	createTriangle(buffer, indexes);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

	// ----------------------------------------
	// Object - Quadrangle
	// ----------------------------------------

	// // Vertex and Index buffers (host)
	// std::vector<glm::vec4> buffer;
	// std::vector<glm::ivec4> indexes;

	// // Create Quadrangle
	// createQuad(buffer, indexes);
	// // createQuads(buffer, indexes, 5, 5);

	// // Load Vertex Data
	// glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// // Load Element Data
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec4), indexes.data(), GL_STATIC_DRAW);

	// ----------------------------------------
	// Vertex Array Object
	// ----------------------------------------

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// ----------------------------------------
	// Model Matrix
	// ----------------------------------------
	float modelThetaX =  0.0f;
	float modelThetaY =  0.0f;
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
							glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) * 
							glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));

	
	// Copy Rotation Matrix to Shader
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// ----------------------------------------
	// View Matrix
	// ----------------------------------------
	// Copy to Reflection program
	glUseProgram(program);

	// Copy Model Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(program, "u_IView"), 1, GL_FALSE, glm::value_ptr(glm::inverse(camera->getViewMatrix())));

	// ----------------------------------------
	// Projection Matrix
	// ----------------------------------------
	glm::mat4 projectionMatrix(1.0f);
	
	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

	// Copy Projection Matrix to Shader
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	float time = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to black
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update Time
		float current_time = glfwGetTime();
		float dt = current_time - time;
		time = current_time;

		// ----------------------------------------
		// Update Model Matrix
		if(glfwGetKey(window, GLFW_KEY_UP)) {
			// Key - Up Arrow
			modelThetaX -= 1.5f * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_DOWN)) {
			// Key - Down Arrow
			modelThetaX += 1.5f * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_LEFT)) {
			// Key - Left Arrow
			modelThetaY -= 1.5f * dt;
		}

		if(glfwGetKey(window, GLFW_KEY_RIGHT)) {
			// Key - Right Arrow
			modelThetaY += 1.5f * dt;
		}
		// ----------------------------------------

		// ----------------------------------------
		// Update Camera
		camera->update(dt);
		// ----------------------------------------


		// ----------------------------------------
		// Update Model Matrix
		modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) * 
					  glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f)) *
					  glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f));

		// Copy Model Matrix to Shader
		glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

		// Copy View Matrix to Shader
		glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(program, "u_IView"), 1, GL_FALSE, glm::value_ptr(glm::inverse(camera->getViewMatrix())));

		// ----------------------------------------
		// Update Tessellation Parameters
		glUniform1f(glGetUniformLocation(program, "u_TessLevelInner1"), tessLevelInner1);
		glUniform1f(glGetUniformLocation(program, "u_TessLevelInner2"), tessLevelInner2);
		glUniform1f(glGetUniformLocation(program, "u_TessLevelOuter1"), tessLevelOuter1);
		glUniform1f(glGetUniformLocation(program, "u_TessLevelOuter2"), tessLevelOuter2);
		glUniform1f(glGetUniformLocation(program, "u_TessLevelOuter3"), tessLevelOuter3);
		glUniform1f(glGetUniformLocation(program, "u_TessLevelOuter4"), tessLevelOuter4);

		// Update Time
		glUniform1f(glGetUniformLocation(program, "u_time"), glfwGetTime());

		// ----------------------------------------
		// Draw Object
		// ----------------------------------------
		// Use Program
		glUseProgram(program);

		// Bind Vertex Array Object
		glBindVertexArray(vao);

		// ----------------------------------------
		// Draw Triangles
		// ----------------------------------------
		// Configure Patches
		glPatchParameteri(GL_PATCH_VERTICES, 3);

		// Draw Elements (Patches)
		glDrawElements(GL_PATCHES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);
		// ----------------------------------------

		// // ----------------------------------------
		// // Draw Quadrangles
		// // ----------------------------------------
		// // Configure Patches
		// glPatchParameteri(GL_PATCH_VERTICES, 4);

		// // Draw Elements (Patches)
		// glDrawElements(GL_PATCHES, indexes.size() * 4, GL_UNSIGNED_INT, NULL);
		// // ----------------------------------------

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


