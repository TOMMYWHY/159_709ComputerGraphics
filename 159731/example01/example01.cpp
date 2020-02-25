// System Headers
#include <iostream>

// GLFW Headers
#include <GLFW/glfw3.h>


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
// Example 01 - Simple Window
// --------------------------------------------------------------------------------
int main() {
	// Set Error Callback
	glfwSetErrorCallback(onError);

	// Initialise GLFW
	if (!glfwInit()) {
		// Error - Abort
		return 1;
	}

	// Create Window
	GLFWwindow *window = createWindow(600, 600, "Example 01", 3, 2);

	// Check Window
	if (window == NULL) {
		// Print Error Message
		std::cerr << "Error: create window or context failed." << std::endl;

		// Return Error
		return 1;
	}

	// Main Render loop
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to green
		glClearColor(0.f, 0.5f, 0.f, 0.f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}


