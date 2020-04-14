#ifndef IMAGE_H
#define IMAGE_H

// System Headers
#include <iostream>

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

// --------------------------------------------------------------------------------
// Image Functions
// --------------------------------------------------------------------------------

// Load an image from file
unsigned char* loadImage(const char *filename, int &x, int &y, int &n, bool flip);

// Load a Texture from file
GLuint loadTexture2D(const char *filename, int &x, int &y, int &n, GLint minFilter=GL_LINEAR_MIPMAP_NEAREST, GLint magFilter=GL_LINEAR, GLint textureWrapS=GL_REPEAT, GLint textureWrapT=GL_REPEAT);

// Create a Texture from data
GLuint createTexture2D(const unsigned char *image, int width, int height, int n, GLint minFilter=GL_LINEAR_MIPMAP_NEAREST, GLint magFilter=GL_LINEAR, GLint textureWrapS=GL_REPEAT, GLint textureWrapT=GL_REPEAT);

// Create a Texture from float data
GLuint createTexture2D(const float *image, int width, int height, int n, GLint minFilter=GL_LINEAR_MIPMAP_NEAREST, GLint magFilter=GL_LINEAR, GLint textureWrapS=GL_REPEAT, GLint textureWrapT=GL_REPEAT);

// Load a 2D surface texture from normal and height image files
GLuint loadSurfaceTexture2D(std::string normal_filename, std::string height_filename, int &x, int &y, int &n);

// Load a CubeMap Texture from file
GLuint loadTextureCubeMap(const char *filename[6], int &x, int &y, int &n);

#endif // IMAGE_H