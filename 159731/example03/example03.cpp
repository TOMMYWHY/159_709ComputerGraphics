// System Headers
#include <iostream>
#include <fstream>

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
// GLFW Functions
// --------------------------------------------------------------------------------

// Create a GLFW Window
GLFWwindow* createWindow(int width, int height, const char *title, int major = 3, int minor = 2, GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL) {
	// Request an OpenGL context with specific features
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

	// If Version is 3 or higher
	if (major >= 3) {
		// Request Forward Compatibility
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		// If version is 3.2 or higher
		if (major > 3 || minor >= 2) {
			// Request Core Profile
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
	}

	// Create GLFW Window
	GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);

	// Check Returned Window
	if (window == NULL) {
		return NULL;
	}

	// Set Context
	glfwMakeContextCurrent(window);

	// Set window callback functions
	glfwSetFramebufferSizeCallback(window, onFramebufferSize);
	glfwSetWindowCloseCallback(window, onWindowClose);

	// Return GLFW window
	return window;
}

// --------------------------------------------------------------------------------
// Shader Functions
// --------------------------------------------------------------------------------

// Read file contents
char* readFile(const char *filename) {
	// Open File
	std::ifstream input(filename);

	// Check file is open
	if(!input.good()) {
		// Print Error
		std::cerr << "Error: Could not open " << filename << std::endl;

		// Return Error
		return 0;
	}

	// Find end of file
	input.seekg(0, std::ios::end);

	// Calculate Size
	size_t size = input.tellg();

	// Allocate required memory
	char *data = new char[size+1];

	// Rewind to beginning
	input.seekg(0, std::ios::beg);

	// Read file into memory
	input.read(data, size);

	// Append '\0'
	data[size] = '\0';

	// Close file
	input.close();

	// Return file contents
	return data;
}

// Check the status of a Shader
GLuint checkShader(GLuint shader) {
	// Compile status
	GLint status = 0;

	// Check compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	// Error detected
	if(status != GL_TRUE) {
		// Get error message length
		int size;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

		// Get error message
		char *message = new char[size];
		glGetShaderInfoLog(shader, size, &size, message);

		// Print error message
		std::cerr << message << std::endl;

		// Delete message
		delete[] message;

		// Return error
		return GL_FALSE;
	}

	// Return success
	return GL_TRUE;
}

// Check the status of a Program
GLuint checkProgram(GLuint program) {
	// Link status
	GLint status = 0;

	// Check link status
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	// Error detected
	if(status != GL_TRUE) {
		// Get error message length
		int size;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);

		// Get error message
		char *message = new char[size];
		glGetProgramInfoLog(program, size, &size, message);

		// Print error message
		std::cerr << message << std::endl;

		// Delete message
		delete[] message;

		// Return error
		return GL_FALSE;
	}

	// Return success
	return GL_TRUE;
}

// Load and Compiler Shader for source file
GLuint loadShader(GLuint type, const char *filename) {
	// Read the shader source from file
	char *source = readFile(filename);

	// Check shader source
	if(source == 0) {
		// Return Error
		return 0;
	}

	// Create the OpenGL Shaders
	GLuint shader = glCreateShader(type);

	// Load the source into the shaders
	glShaderSource(shader, 1, &source, NULL);

	// Compile the Shaders
	glCompileShader(shader);

	// Check shaders for errors
	if(checkShader(shader) == GL_TRUE) {
		// Log
		std::cout << "Loaded: " << filename << std::endl;
	} else {
		// Print Error
		std::cerr << "Error: could not compile " << filename << std::endl;

		// Delete shader source
		delete[] source;

		// Return Error
		return 0;
	}

	// Delete shader source
	delete[] source;

	// Return shader
	return shader;
}

GLuint loadProgram(const char *vert_file, const char *ctrl_file, const char *eval_file, const char *geom_file, const char *frag_file) {
	// Create new OpenGL program
	GLuint program = glCreateProgram();

	// Shader Handles
	GLuint vert_shader = 0;
	GLuint ctrl_shader = 0;
	GLuint eval_shader = 0;
	GLuint geom_shader = 0;
	GLuint frag_shader = 0;

	// Load Shaders
	if(vert_file != NULL) vert_shader = loadShader(GL_VERTEX_SHADER,          vert_file);
	if(ctrl_file != NULL) ctrl_shader = loadShader(GL_TESS_CONTROL_SHADER,    ctrl_file);
	if(eval_file != NULL) eval_shader = loadShader(GL_TESS_EVALUATION_SHADER, eval_file);
	if(geom_file != NULL) geom_shader = loadShader(GL_GEOMETRY_SHADER,        geom_file);
	if(frag_file != NULL) frag_shader = loadShader(GL_FRAGMENT_SHADER,        frag_file);

	// Attach shaders
	if(vert_shader != 0) glAttachShader(program, vert_shader);
	if(ctrl_shader != 0) glAttachShader(program, ctrl_shader);
	if(eval_shader != 0) glAttachShader(program, eval_shader);
	if(geom_shader != 0) glAttachShader(program, geom_shader);
	if(frag_shader != 0) glAttachShader(program, frag_shader);

	// Check Vertex Shader
	if(vert_shader == 0) {
		// Print Error
		std::cerr << "Error: program missing vertex shader." << std::endl;

		// Delete Shaders
		if(vert_shader != 0) glDeleteShader(vert_shader);
		if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
		if(eval_shader != 0) glDeleteShader(eval_shader);
		if(geom_shader != 0) glDeleteShader(geom_shader);
		if(frag_shader != 0) glDeleteShader(frag_shader);

		// Return Error
		return 0;
	}

	// Check Fragment Shader
	if(frag_shader == 0) {
		// Print Error
		std::cerr << "Error: program missing fragment shader." << std::endl;

		// Delete Shaders
		if(vert_shader != 0) glDeleteShader(vert_shader);
		if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
		if(eval_shader != 0) glDeleteShader(eval_shader);
		if(geom_shader != 0) glDeleteShader(geom_shader);
		if(frag_shader != 0) glDeleteShader(frag_shader);

		// Return Error
		return 0;
	}

	// Link program
	glLinkProgram(program);

	// Delete Shaders (no longer needed)
	if(vert_shader != 0) glDeleteShader(vert_shader);
	if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
	if(eval_shader != 0) glDeleteShader(eval_shader);
	if(geom_shader != 0) glDeleteShader(geom_shader);
	if(frag_shader != 0) glDeleteShader(frag_shader);

	// Check program for errors
	if(checkProgram(program) == GL_TRUE) {
		// Print Log
		std::cout << "Loaded: program" << std::endl;
	} else {
		// Print Error
		std::cerr << "Error: could not link program" << std::endl;

		// Return Error
		return 0;
	}

	// Return program
	return program;
}

// --------------------------------------------------------------------------------
// Example 03 - Buffer Objects
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
	GLFWwindow *window = createWindow(600, 600, "Example 03 - Triangle", 3, 2);

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

	// ----------------------------------------
	// Create Triangle Data
	// ----------------------------------------

	// Triangle Vertexes (and colours)
	GLfloat buffer[18];

	buffer[0]  =  0.0f; buffer[1]  =  0.577f; buffer[2]  =  0.0f;
	buffer[3]  =  1.0f; buffer[4]  =  0.0f;   buffer[5]  =  0.0f;

	buffer[6]  =  0.5f; buffer[7]  = -0.289f; buffer[8]  =  0.0f;
	buffer[9]  =  0.0f; buffer[10] =  1.0f;   buffer[11] =  0.0f;

	buffer[12] = -0.5f; buffer[13] = -0.289f; buffer[14] =  0.0f;
	buffer[15] =  0.0f; buffer[16] =  0.0f;   buffer[17] =  1.0f;

	// Triangle Indexes
	GLuint indexes[3];
	indexes[0] = 0;
	indexes[1] = 2;
	indexes[2] = 1;

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint program = loadProgram("vert.glsl", NULL, NULL, NULL, "frag.glsl");

	// Vertex Array Object (VAO)
	GLuint vao = 0;
	
	// Vertex Buffer Object (VBO)
	GLuint vbo = 0;

	// Element Buffer Object (EBO)
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
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), buffer, GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indexes, GL_STATIC_DRAW);

	// Get Position Attribute location (must match name in shader)
	GLuint pos = glGetAttribLocation(program, "vert_Position");

	// Get Colour Attribute location (must match name in shader)
	GLuint col = glGetAttribLocation(program, "vert_Colour");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(col);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to green
		glClearColor(0.f, 0.0f, 0.f, 0.f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use Program
		glUseProgram(program);

		// Bind Vertex Array Object
		glBindVertexArray(vao);

		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

		// Unbind Vertex Array Object
		glBindVertexArray(0);

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


