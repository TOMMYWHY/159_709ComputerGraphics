//
// Created by Tommy on 2020/4/15.
//

#ifndef OPENGL_DEMO_SHADE_H
#define OPENGL_DEMO_SHADE_H


#include <string>
#include <OpenGL/OpenGL.h>
//#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

using namespace std;


class Shade {
public:
    GLuint ID;
    string vertexString;
    string fragmentString;
    const char* vertexSource;
    const char* fragmentSource;
    Shade(const char* vertexPath, const char* fragmentPath);
    ~Shade();
    void test();
    void use();

private:
    void checkCompileErrors(GLuint shader, std::string type);
};


#endif //OPENGL_DEMO_SHADE_H
