#ifndef GEOMETRY_H
#define GEOMETRY_H

// System Headers
#include <iostream>
#include <vector>

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
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

// Create Triangle with Positions and Normals
void createTriangle(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// Create Quad with Positions and Normals
void createQuad(std::vector<glm::vec4> &buffer, std::vector<glm::ivec4> &indexes);

// Create Quads with Positions and Normals
void createQuads(std::vector<glm::vec4> &buffer, std::vector<glm::ivec4> &indexes, int X, int Y);

#endif // GEOMETRY_H