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

// --------------------------------------------------------------------------------
// Create Cube with Positions and Normals (Interleaved)
void createCubeInterleaved(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create Cube with Positions and Normals
void createCubeSeparate(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create Tetrahedron with Positions and Colours (Interleaved)
void createTetrahedronInterleaved(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create Tetrahedron with Positions and Colours (Separate)
void createTetrahedronSeparate(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

#endif // GEOMETRY_H