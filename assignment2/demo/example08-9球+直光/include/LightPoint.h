//
// Created by Tommy on 2020/4/12.
//

#ifndef OPENGL_START_08_LIGHTPOINT_H
#define OPENGL_START_08_LIGHTPOINT_H
// System Headers
#include <iostream>
#include <fstream>

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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>



class LightPoint {
public:
    LightPoint(glm::vec4 _position, glm::vec4 _angles, glm::vec4 _color);

    ~LightPoint( );

    glm::vec4 position;
    glm::vec4 angles;
    glm::vec4 direction;
    glm::vec4 color;

    float constant;
    float linear;
    float quadratic;


};


#endif //OPENGL_START_08_LIGHTPOINT_H
