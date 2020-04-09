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
// Example 07 - Texture Mapping
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

	// ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// ----------------------------------------
	// Create Object
	// ----------------------------------------

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> bufferEarth;
	std::vector<glm::ivec3> indexesEarth;

	// Create Textured Cube
//	createTexturedCube(buffer, indexes);
    createSphere(bufferEarth, indexesEarth,0.8f,50,50);




	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint program  = loadProgram("./shader/texture.vert.glsl",  NULL, NULL, NULL, "./shader/texture.frag.glsl");

	// Vertex Array Objects (VAO)
	GLuint vaoEarth = 0;
	
	// Vertex Buffer Objects (VBO)
	GLuint vboEarth = 0;

	// Element Buffer Objects (EBO)
	GLuint eboEarth = 0;

	// ----------------------------------------
	// Load Texture Map from file
	int x, y, n;
//	unsigned char *image = loadImage("./images/dark_red_brick.jpg", x, y, n, false);
//    	unsigned char *image = loadImage("./images/earth.bmp", x, y, n, false);
	unsigned char *imageEarth = loadImage("./images/earthmap.tga", x, y, n, false);

	// Check image result
	if(imageEarth == NULL) {
		// Return error
		return 0;
	}

	// Texture
	GLuint textureEarth;

	// Generate texture
	glGenTextures(1, &textureEarth);

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, textureEarth);

	// ------------------------------
	// No Mip-Mapping
	// ------------------------------
	// Copy data to texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageEarth);

	// // Configure texture
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // No mip-mapping
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Configure texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // No mip-mapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configure Texture Coordinate Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);


	// ------------------------------
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Delete image data
	delete[] imageEarth;
	imageEarth = NULL;

	// ----------------------------------------
	// Cube
	// ----------------------------------------

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &vaoEarth);
	glGenBuffers(1, &vboEarth);
	glGenBuffers(1, &eboEarth);

	// Bind VAO, VBO & EBO
	glBindVertexArray(vaoEarth);
	glBindBuffer(GL_ARRAY_BUFFER, vboEarth);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboEarth);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, bufferEarth.size() * sizeof(glm::vec4), bufferEarth.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexesEarth.size() * sizeof(glm::ivec3), indexesEarth.data(), GL_STATIC_DRAW);

	// Get Position Attribute location (must match name in shader)
	GLuint posLocEarth = glGetAttribLocation(program, "vert_Position");

	// Get Normal Attribute location (must match name in shader)
	GLuint norLocEarth = glGetAttribLocation(program, "vert_Normal");

	// Get Texture Attribute location (must match name in shader)
	GLuint texLocEarth = glGetAttribLocation(program, "vert_UV");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(posLocEarth, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(norLocEarth, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
	glVertexAttribPointer(texLocEarth, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(posLocEarth);
	glEnableVertexAttribArray(norLocEarth);
	glEnableVertexAttribArray(texLocEarth);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ----------------------------------------
	// Use Program
	glUseProgram(program);

	// ----------------------------------------
	// Get Sampler Location
	GLuint textureMapLocEarth = glGetUniformLocation(program, "u_texture_Map");

	// Set Sample Texture Unit
	glUniform1i(textureMapLocEarth, 0);

	// ----------------------------------------
	// Model Matrix
	// ----------------------------------------
	// float modelThetaX =  0.3f;
	// float modelThetaY = -0.5f;
	float modelThetaX =  0.0f;
	float modelThetaY =  0.0f;
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
							glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) *
							glm::rotate(   glm::mat4(1.0f), modelThetaY, glm::vec3(0.0f, 1.0f, 0.0f));
//                            glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

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

	// Get time
	float last = glfwGetTime();

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

		// ----------------------------------------
		// Get current time
		float current = glfwGetTime();
		float dt = current - last;
		last = current;

        // Recompute Model Matrix
        modelMatrix = glm::translate(glm::mat4(1.0f),              glm::vec3(0.0f, 0.0f, 0.0f)) *
                      glm::rotate(   glm::mat4(1.0f), modelThetaX, glm::vec3(1.0f, 0.0f, 0.0f)) *
                      glm::rotate(   glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Copy Rotation Matrix to Shader
        glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

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
        if(glfwGetKey(window, GLFW_KEY_LEFT)) {
            // Move Away
            viewPosition.x -= 1.0f * dt;

            // Construct View Matrix
            viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

            // Copy View Matrix to Shader
            glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT)) {
            // Move Away
            viewPosition.x += 1.0f * dt;

            // Construct View Matrix
            viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);

            // Copy View Matrix to Shader
            glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        }

		// ----------------------------------------

		// Bind Vertex Array Object
		glBindVertexArray(vaoEarth);


		// Set active Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Bind Texture Map
		glBindTexture(GL_TEXTURE_2D, textureEarth);

		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, indexesEarth.size() * 3, GL_UNSIGNED_INT, NULL);

		// Set active Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Unbind Texture Map
		glBindTexture(GL_TEXTURE_2D, 0);

		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Delete VAO, VBO & EBO
	glDeleteVertexArrays(1, &vaoEarth);
	glDeleteBuffers(1, &vboEarth);
	glDeleteBuffers(1, &eboEarth);

	// Delete Program
	glDeleteProgram(program);

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}


