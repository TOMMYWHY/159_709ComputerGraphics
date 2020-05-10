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

	// GLM Headers
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
#elif defined(__APPLE__)
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Project Headers
#include "shader.h"
#include "utils.h"
#include "geometry.h"

enum orientation_mode{GIMBAL, GLOBAL_MATRIX, LOCAL_MATRIX, GLOBAL_QUATERNION, LOCAL_QUATERNION};

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
// Orientation Mode
// orientation_mode mode = GIMBAL;
// orientation_mode mode = GLOBAL_MATRIX;
// orientation_mode mode = LOCAL_MATRIX;
//orientation_mode mode = GLOBAL_QUATERNION;
 orientation_mode mode = LOCAL_QUATERNION;

void update_keyboard(GLFWwindow *window, glm::mat4 &modelMatrix, float dt) {
	// Gimbal
	static glm::vec3 rotations(0.0f, 0.0f, 0.0f);

	// Quaternion
	static glm::quat modelQuaternion(1.0f, 0.0f, 0.0f, 0.0f);

	if(mode == GIMBAL) {
		// ----------------------------------------
		// Angles
		// ----------------------------------------
		// Key Inputs
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			// Pitch +
			rotations.x += 0.5 * dt;
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			// Pitch -
			rotations.x -= 0.5 * dt;
		}
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			// Yaw +
			rotations.y += 0.5 * dt;
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			// Yaw -
			rotations.y -= 0.5 * dt;
		}
		if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			// Roll -
			rotations.z += 0.5 * dt;
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			// Roll +
			rotations.z -= 0.5 * dt;
		}
		// ----------------------------------------
		// Calculate Model Matrix
		glm::mat4 modelRx = glm::rotate(glm::mat4(1.0f), rotations.x, glm::vec3(1,0,0));
		glm::mat4 modelRy = glm::rotate(glm::mat4(1.0f), rotations.y, glm::vec3(0,1,0));
		glm::mat4 modelRz = glm::rotate(glm::mat4(1.0f), rotations.z, glm::vec3(0,0,1));

		modelMatrix = modelRy * modelRx * modelRz;
		// ----------------------------------------
	} else if(mode == GLOBAL_MATRIX) {
		// ----------------------------------------
		// Matrix Transformation - Global
		// ----------------------------------------
		// Key Inputs
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			// Pitch +
			modelMatrix = glm::rotate(glm::mat4(1.0f),  0.5f * dt, glm::vec3(1,0,0)) * modelMatrix;
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			// Pitch -
			modelMatrix = glm::rotate(glm::mat4(1.0f), -0.5f * dt, glm::vec3(1,0,0)) * modelMatrix;
		}
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			// Yaw +
			modelMatrix = glm::rotate(glm::mat4(1.0f),  0.5f * dt, glm::vec3(0,1,0)) * modelMatrix;
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			// Yaw -
			modelMatrix = glm::rotate(glm::mat4(1.0f), -0.5f * dt, glm::vec3(0,1,0)) * modelMatrix;
		}
		if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			// Roll -
			modelMatrix = glm::rotate(glm::mat4(1.0f),  0.5f * dt, glm::vec3(0,0,1)) * modelMatrix;
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			// Roll +
			modelMatrix = glm::rotate(glm::mat4(1.0f), -0.5f * dt, glm::vec3(0,0,1)) * modelMatrix;
		}
		// ----------------------------------------
	} else if(mode == LOCAL_MATRIX) {
		// ----------------------------------------
		// Matrix Transformation - Local
		// ----------------------------------------
		// Key Inputs
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			// Pitch +
			modelMatrix = modelMatrix * glm::rotate(glm::mat4(1.0f),  0.5f * dt, glm::vec3(1,0,0));
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			// Pitch -
			modelMatrix = modelMatrix * glm::rotate(glm::mat4(1.0f), -0.5f * dt, glm::vec3(1,0,0));
		}
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			// Yaw +
			modelMatrix = modelMatrix * glm::rotate(glm::mat4(1.0f),  0.5f * dt, glm::vec3(0,1,0));
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			// Yaw -
			modelMatrix = modelMatrix * glm::rotate(glm::mat4(1.0f), -0.5f * dt, glm::vec3(0,1,0));
		}
		if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			// Roll -
			modelMatrix = modelMatrix * glm::rotate(glm::mat4(1.0f),  0.5f * dt, glm::vec3(0,0,1));
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			// Roll +
			modelMatrix = modelMatrix * glm::rotate(glm::mat4(1.0f), -0.5f * dt, glm::vec3(0,0,1));
		}
	} else if(mode == GLOBAL_QUATERNION) {
		// ----------------------------------------
		// Quaternion Transformation - Global
		// ----------------------------------------
		// Key Inputs
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			// Pitch +
			modelQuaternion = glm::quat(glm::cos(0.25f * dt),  glm::sin(0.25f * dt), 0.0f, 0.0f) * modelQuaternion;
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			// Pitch -
			modelQuaternion = glm::quat(glm::cos(0.25f * dt), -glm::sin(0.25f * dt), 0.0f, 0.0f) * modelQuaternion;
		}
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			// Yaw +
			modelQuaternion = glm::quat(glm::cos(0.25f * dt), 0.0f,  glm::sin(0.25f * dt), 0.0f) * modelQuaternion;
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			// Yaw -
			modelQuaternion = glm::quat(glm::cos(0.25f * dt), 0.0f, -glm::sin(0.25f * dt), 0.0f) * modelQuaternion;
		}
		if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			// Roll -
			modelQuaternion = glm::quat(glm::cos(0.25f * dt), 0.0f, 0.0f,  glm::sin(0.25f * dt)) * modelQuaternion;
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			// Roll +
			modelQuaternion = glm::quat(glm::cos(0.25f * dt), 0.0f, 0.0f, -glm::sin(0.25f * dt)) * modelQuaternion;
		}

		// Check Quaternion
		float w = modelQuaternion.w;
		float x = modelQuaternion.x;
		float y = modelQuaternion.y;
		float z = modelQuaternion.z;

		// Check Quaternion Magnitude
		if(glm::abs((x*x + y*y + z*z + w*w) - 1.0f) > 0.001) {
			// Renormalise Model Quaternion
			std::cout << "Renormalising Model Orientation" << std::endl;
			modelQuaternion = glm::normalize(modelQuaternion);
		}

		// Convert to 4x4 Matrix
		modelMatrix = glm::mat4_cast(modelQuaternion);
		// ----------------------------------------
	} else if(mode == LOCAL_QUATERNION) {
		// ----------------------------------------
		// Matrix Transformation - Local
		// ----------------------------------------
		// Key Inputs
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			// Pitch +
			modelQuaternion = modelQuaternion * glm::quat(glm::cos(0.25f * dt),  glm::sin(0.25f * dt), 0.0f, 0.0f);
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			// Pitch -
			modelQuaternion = modelQuaternion * glm::quat(glm::cos(0.25f * dt), -glm::sin(0.25f * dt), 0.0f, 0.0f);
		}
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			// Yaw +
			modelQuaternion = modelQuaternion * glm::quat(glm::cos(0.25f * dt), 0.0f,  glm::sin(0.25f * dt), 0.0f);
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			// Yaw -
			modelQuaternion = modelQuaternion * glm::quat(glm::cos(0.25f * dt), 0.0f, -glm::sin(0.25f * dt), 0.0f);
		}
		if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			// Roll -
			modelQuaternion = modelQuaternion * glm::quat(glm::cos(0.25f * dt), 0.0f, 0.0f,  glm::sin(0.25f * dt));
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			// Roll +
			modelQuaternion = modelQuaternion * glm::quat(glm::cos(0.25f * dt), 0.0f, 0.0f, -glm::sin(0.25f * dt));
		}

		// Check Quaternion
		float w = modelQuaternion.w;
		float x = modelQuaternion.x;
		float y = modelQuaternion.y;
		float z = modelQuaternion.z;

		// Check Quaternion Magnitude
		if(glm::abs((x*x + y*y + z*z + w*w) - 1.0f) > 0.00001) {
			// Renormalise Model Quaternion
			std::cout << "Renormalising Model Orientation" << std::endl;
			modelQuaternion = glm::normalize(modelQuaternion);
		}

		// Convert to 4x4 Matrix
		modelMatrix = glm::mat4_cast(modelQuaternion);
	}
}

// --------------------------------------------------------------------------------
// Example 12 - Orientations
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
	GLFWwindow *window = createWindow(600, 600, "Example 12 - Orientations", 3, 2);

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
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint phongProgram  = loadProgram("./shader/phong.vert.glsl",  NULL, NULL, NULL, "./shader/phong.frag.glsl");
	GLuint goraudProgram = loadProgram("./shader/goraud.vert.glsl", NULL, NULL, NULL, "./shader/goraud.frag.glsl");
	GLuint axesProgram   = loadProgram("./shader/axis.vert.glsl", NULL, NULL, NULL, "./shader/axis.frag.glsl");

	// GLuint program = goraudProgram;
	GLuint program = phongProgram;

	// ----------------------------------------
	// Object
	// ----------------------------------------

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create Brick
	createBrick(buffer, indexes);

	// // Create Cube
	// createCube(buffer, indexes);

	// // Create Tetrahedron
	// createTetrahedron(buffer, indexes);

	// Create Torus
	// createTorus(buffer, indexes, 2.0f, 0.9f, 10, 10);

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

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

	glUseProgram(program);

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
	// Axes
	// ----------------------------------------

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> axes_buffer;
	std::vector<glm::ivec2> axes_indexes;

	// Create Axes
	createAxes(axes_buffer, axes_indexes);

	// Vertex Array Objects (VAO)
	GLuint axes_vao = 0;
	
	// Vertex Buffer Objects (VBO)
	GLuint axes_vbo = 0;

	// Element Buffer Objects (EBO)
	GLuint axes_ebo = 0;

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &axes_vao);
	glGenBuffers(1,      &axes_vbo);
	glGenBuffers(1,      &axes_ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(axes_vao);
	glBindBuffer(GL_ARRAY_BUFFER, axes_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axes_ebo);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, axes_buffer.size() * sizeof(glm::vec4), axes_buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, axes_indexes.size() * sizeof(glm::ivec2), axes_indexes.data(), GL_STATIC_DRAW);

	glUseProgram(axesProgram);

	// Get Position Attribute location (must match name in shader)
	GLuint axesPosLoc = glGetAttribLocation(axesProgram, "vert_Position");

	// Get Normal Attribute location (must match name in shader)
	GLuint axesColLoc = glGetAttribLocation(axesProgram, "vert_Colour");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(axesPosLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(axesColLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(axesPosLoc);
	glEnableVertexAttribArray(axesColLoc);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ----------------------------------------
	// Model Matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// ----------------------------------------
	// View Matrix
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -15.0f));
	viewMatrix = viewMatrix * glm::rotate(glm::mat4(1.0f), -0.2f, glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), 0.2f, glm::vec3(1, 0, 0));

	// ----------------------------------------
	// Projection Matrix
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

	// ----------------------------------------
	// Copy Matrices to Object Shader
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"),      1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),       1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// ----------------------------------------

	// ----------------------------------------
	// Copy Matrices to Axes Shader
	glUseProgram(axesProgram);
	glUniformMatrix4fv(glGetUniformLocation(axesProgram, "u_Model"),      1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(axesProgram, "u_View"),       1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(axesProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// ----------------------------------------

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	float time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to dark grey
		glClearColor(0.15f, 0.15f, 0.15f, 0.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update Time
		float current_time = glfwGetTime();
		float dt = current_time - time;
		time = current_time;

		// ----------------------------------------
		// Poll Keyboard
		// ----------------------------------------
		update_keyboard(window, modelMatrix, dt);
		
		// ----------------------------------------
		// Copy Rotation Matrix to Shaders
		// ----------------------------------------
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program,     "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glUseProgram(axesProgram);
		if(mode == GIMBAL || mode == GLOBAL_MATRIX || mode == GLOBAL_QUATERNION) {
			glUniformMatrix4fv(glGetUniformLocation(axesProgram, "u_Model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		} else {
			glUniformMatrix4fv(glGetUniformLocation(axesProgram, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		}

		// ----------------------------------------
		// Draw Object
		// ----------------------------------------
		// Use Program
		glUseProgram(program);

		// Bind Vertex Array Object
		glBindVertexArray(vao);

		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);

		// Unbind Vertex Array Object
		glBindVertexArray(0);
		// ----------------------------------------

		// ----------------------------------------
		// Draw Axes
		// ----------------------------------------
		// Use Program
		glUseProgram(axesProgram);

		// Bind Vertex Array Object
		glBindVertexArray(axes_vao);

		// Draw Elements (Lines)
		glDrawElements(GL_LINES, axes_indexes.size() * 2, GL_UNSIGNED_INT, NULL);

		// Unbind Vertex Array Object
		glBindVertexArray(0);
		// ----------------------------------------


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


