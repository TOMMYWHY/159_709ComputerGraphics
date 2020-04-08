// System Headers
#include <iostream>
#include <fstream>
#include <cmath>

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

// Project Headers
#include "shader.h"
#include "utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

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
// Transform Functions
// --------------------------------------------------------------------------------

// Create an identity matrix
void identity(float I[16]) {
	I[0]  = 1.0f;  I[4]  = 0.0f;  I[8]  = 0.0f;  I[12] = 0.0f;
	I[1]  = 0.0f;  I[5]  = 1.0f;  I[9]  = 0.0f;  I[13] = 0.0f;
	I[2]  = 0.0f;  I[6]  = 0.0f;  I[10] = 1.0f;  I[14] = 0.0f;
	I[3]  = 0.0f;  I[7]  = 0.0f;  I[11] = 0.0f;  I[15] = 1.0f;
}

// Create a translation matrix with (x,y,z)
void translate(float tx, float ty, float tz, float T[16]) {
	T[0]  = 1.0f;  T[4]  = 0.0f;  T[8]  = 0.0f;  T[12] = tx;
	T[1]  = 0.0f;  T[5]  = 1.0f;  T[9]  = 0.0f;  T[13] = ty;
	T[2]  = 0.0f;  T[6]  = 0.0f;  T[10] = 1.0f;  T[14] = tz;
	T[3]  = 0.0f;  T[7]  = 0.0f;  T[11] = 0.0f;  T[15] = 1.0f;
}

// Create a rotation matrix around the X-axis
void rotateX(float theta, float Rx[16]) {
	// Calculate sin(theta) and cos(theta)
//	cout <<"time:"<<theta <<endl;
	float sinTheta = sin(theta);
	float cosTheta = cos(theta);

	Rx[0]  = 1.0f;  Rx[4]  = 0.0f;      Rx[8]  =      0.0f;  Rx[12] = 0.0f;
	Rx[1]  = 0.0f;  Rx[5]  = cosTheta;  Rx[9]  = -sinTheta;  Rx[13] = 0.0f;
	Rx[2]  = 0.0f;  Rx[6]  = sinTheta;  Rx[10] =  cosTheta;  Rx[14] = 0.0f;
	Rx[3]  = 0.0f;  Rx[7]  = 0.0f;      Rx[11] =      0.0f;  Rx[15] = 1.0f;
}

// Create a rotation matrix around the Y-axis
void rotateY(float theta, float Ry[16]) {
	// Calculate sin(theta) and cos(theta)
	float sinTheta = sin(theta);
	float cosTheta = cos(theta);

	Ry[0]  =  cosTheta;  Ry[4]  = 0.0f;  Ry[8]  =  sinTheta;  Ry[12] = 0.0f;
	Ry[1]  =  0.0f;      Ry[5]  = 1.0f;  Ry[9]  =      0.0f;  Ry[13] = 0.0f;
	Ry[2]  = -sinTheta;  Ry[6]  = 0.0f;  Ry[10] =  cosTheta;  Ry[14] = 0.0f;
	Ry[3]  =  0.0f;      Ry[7]  = 0.0f;  Ry[11] =      0.0f;  Ry[15] = 1.0f;
}

// Create a rotation matrix around the Z-axis
void rotateZ(float theta, float Rz[16]) {
	// Calculate sin(theta) and cos(theta)
	float sinTheta = sin(theta);
	float cosTheta = cos(theta);

	Rz[0]  = cosTheta;  Rz[4]  = -sinTheta;  Rz[8]  = 0.0f;  Rz[12] = 0.0f;
	Rz[1]  = sinTheta;  Rz[5]  =  cosTheta;  Rz[9]  = 0.0f;  Rz[13] = 0.0f;
	Rz[2]  = 0.0f;      Rz[6]  =  0.0f;      Rz[10] = 1.0f;  Rz[14] = 0.0f;
	Rz[3]  = 0.0f;      Rz[7]  =  0.0f;      Rz[11] = 0.0f;  Rz[15] = 1.0f;
}

// Create a rotation matrix around arbitrary axis (rx, ry, rz)
void rotate(float theta, float rx, float ry, float rz, float R[16]) {
	// Calculate sin(theta) and cos(theta)
	float sinTheta = sin(theta);
	float cosTheta = cos(theta);

	float l = sqrt(rx*rx + ry*ry + rz*rz);
	rx /= l;
	ry /= l;
	rz /= l;

	R[0]  = cosTheta + (1-cosTheta)*rx*rx;     R[4]  = (1-cosTheta)*rx*ry - rz*sinTheta;  R[8]  = (1 - cosTheta)*rx*ry + ry*sinTheta;  R[12] = 0.0f;
	R[1]  = (1-cosTheta)*rx*ry + rz*sinTheta;  R[5]  = cosTheta + (1-cosTheta)*ry*ry;     R[9]  = (1 - cosTheta)*ry*rz - rx*sinTheta;  R[13] = 0.0f;
	R[2]  = (1-cosTheta)*rx*rz - ry*sinTheta;  R[6]  = (1-cosTheta)*ry*rz + rx*sinTheta;  R[10] = cosTheta + (1-cosTheta)*rz*rz;       R[14] = 0.0f;
	R[3]  = 0.0f;                              R[7]  = 0.0f;                              R[11] = 0.0f;                                R[15] = 1.0f;
}

// Create a scale matrix
void scale(float sx, float sy, float sz, float S[16]) {
	// Scaling Matrix
	S[0]  = sx;    S[4]  =  0.0f;  S[8]  = 0.0f;  S[12] = 0.0f;
	S[1]  = 0.0f;  S[5]  =  sy;    S[9]  = 0.0f;  S[13] = 0.0f;
	S[2]  = 0.0f;  S[6]  =  0.0f;  S[10] = sz;    S[14] = 0.0f;
	S[3]  = 0.0f;  S[7]  =  0.0f;  S[11] = 0.0f;  S[15] = 1.0f;
}

// Multiply matrix a * b to give c
void multiply44(float a[16], float b[16], float c[16]) {
	// Multiply each row of A with each column of B to give C
	c[0]  = a[0]*b[0]  + a[4]*b[1]  + a[8]*b[2]   + a[12]*b[3];
	c[4]  = a[0]*b[4]  + a[4]*b[5]  + a[8]*b[6]   + a[12]*b[7];
	c[8]  = a[0]*b[8]  + a[4]*b[9]  + a[8]*b[10]  + a[12]*b[11];
	c[12] = a[0]*b[12] + a[4]*b[13] + a[8]*b[14]  + a[12]*b[15];

	c[1]  = a[1]*b[0]  + a[5]*b[1]  + a[9]*b[2]   + a[13]*b[3];
	c[5]  = a[1]*b[4]  + a[5]*b[5]  + a[9]*b[6]   + a[13]*b[7];
	c[9]  = a[1]*b[8]  + a[5]*b[9]  + a[9]*b[10]  + a[13]*b[11];
	c[13] = a[1]*b[12] + a[5]*b[13] + a[9]*b[14]  + a[13]*b[15];

	c[2]  = a[2]*b[0]  + a[6]*b[1]  + a[10]*b[2]  + a[14]*b[3];
	c[6]  = a[2]*b[4]  + a[6]*b[5]  + a[10]*b[6]  + a[14]*b[7];
	c[10] = a[2]*b[8]  + a[6]*b[9]  + a[10]*b[10] + a[14]*b[11];
	c[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];

	c[3]  = a[3]*b[0]  + a[7]*b[1]  + a[11]*b[2]  + a[15]*b[3];
	c[7]  = a[3]*b[4]  + a[7]*b[5]  + a[11]*b[6]  + a[15]*b[7];
	c[11] = a[3]*b[8]  + a[7]*b[9]  + a[11]*b[10] + a[15]*b[11];
	c[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];
}

// Multiply a vector by a scalar
void multiply3(float s, float u[3], float v[3]) {
	v[0] = s * u[0];
	v[1] = s * u[1];
	v[2] = s * u[2];
}

// Multiply a vector by a scalar
void multiply4(float s, float u[4], float v[4]) {
	v[0] = s * u[0];
	v[1] = s * u[1];
	v[2] = s * u[2];
	v[3] = s * u[3];
}

// Calculate the length of a vector
float length3(float v[3]) {
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

// Calculate the length of a vector
float length4(float v[4]) {
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
}

// Normalize a vector //
void normalize(float v[3], float u[3]) {
	return multiply3(1.0f/length3(v), v, u);
}

// Calculate the cross product of two vectors
void cross_product(float a[3], float b[3], float c[3]) {
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
}

// Calculate the dot product of two vectors
float dot_product3(float a[3], float b[3]) {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

// Calculate the dot product of two vectors
float dot_product4(float a[4], float b[4]) {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
}

// View Transform - forwards and up must be unit vectors
void view(float p[4], float f[3], float u[3], float V[16]) {
	// Calculate right vector
	float r[3];
	cross_product(f, u, r);

	// View rotation and translation
	float Vr[16], Vt[16];

	// Set view rotation
	Vr[0]  =  r[0];  Vr[4]  =  r[1];  Vr[8]  =  r[2];  Vr[12] =  0.0f;
	Vr[1]  =  u[0];  Vr[5]  =  u[1];  Vr[9]  =  u[2];  Vr[13] =  0.0f;
	Vr[2]  = -f[0];  Vr[6]  = -f[1];  Vr[10] = -f[2];  Vr[14] =  0.0f;
	Vr[3]  =  0.0f;  Vr[7]  =  0.0f;  Vr[11] =  0.0f;  Vr[15] =  1.0f;

	// Set view translation
	translate(-p[0], -p[1], -p[2], Vt);

	// Calculate view transform
	multiply44(Vr, Vt, V);
}

// Create an Orthographic Projection matrix
void orthographic(float width, float height, float near1, float far1, float matrix[16]) {
	matrix[0]  = 2.0/width;  matrix[4]  = 0.0f;         matrix[8]  =  0.0f;             matrix[12] = 0.0f;
	matrix[1]  = 0.0f;       matrix[5]  = 2.0f/height;  matrix[9]  =  0.0f;             matrix[13] = 0.0f;
	matrix[2]  = 0.0f;       matrix[6]  = 0.0f;         matrix[10] = -2.0f / (far1-near1);  matrix[14] = -(far1+near1) / (far1-near1);
	matrix[3]  = 0.0f;       matrix[7]  = 0.0f;         matrix[11] =  0.0f;             matrix[15] = 1.0f;
}

// Create a Perspective Projection matrix
void perspective(float aspect, float fov, float near1, float far1, float matrix[16]) {
	// Calculate f
	float f = 1.0f / tan(fov * 0.5);

	// Create Perspective matrix
	matrix[0]  = f/aspect;  matrix[4]  = 0.0f;  matrix[8]  =  0.0f;                  matrix[12] = 0.0f;
	matrix[1]  = 0.0f;      matrix[5]  = f;     matrix[9]  =  0.0f;                  matrix[13] = 0.0f;
	matrix[2]  = 0.0f;      matrix[6]  = 0.0f;  matrix[10] = (far1+near1)/(near1-far1);  matrix[14] = (2*far1*near1) / (near1 - far1);
	matrix[3]  = 0.0f;      matrix[7]  = 0.0f;  matrix[11] =  -1.0f;                 matrix[15] = 0.0f;
}

// --------------------------------------------------------------------------------
// Example 04 - Transforms
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
	GLFWwindow *window = createWindow(600, 600, "Example 05 - Transforms - Cube", 3, 2);

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
	// Create Cube Data
	// ----------------------------------------

	// Triangle Vertexes (and colours)
	GLfloat buffer[144];
	int i = 0;

	// Top - Red
	buffer[i++] = -1.0f;  buffer[i++] =  1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  0.72f; buffer[i++] =  0.07f;  buffer[i++] =  0.2f;

	buffer[i++] =  1.0f;  buffer[i++] =  1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  0.72f; buffer[i++] =  0.07f;  buffer[i++] =  0.2f;

	buffer[i++] =  1.0f;  buffer[i++] =  1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  0.72f; buffer[i++] =  0.07f;  buffer[i++] =  0.2f;

	buffer[i++] = -1.0f;  buffer[i++] =  1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  0.72f; buffer[i++] =  0.07f;  buffer[i++] =  0.2f;

	// Bottom - Orange
	buffer[i++] = -1.0f; buffer[i++] = -1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.35f;  buffer[i++] =  0.0f;

	buffer[i++] =  1.0f; buffer[i++] = -1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.35f;  buffer[i++] =  0.0f;

	buffer[i++] =  1.0f; buffer[i++] = -1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.35f;  buffer[i++] =  0.0f;

	buffer[i++] = -1.0f; buffer[i++] = -1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.35f;  buffer[i++] =  0.0f;

	// Front - Yellow
	buffer[i++] = -1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.84f;  buffer[i++] =  0.0f;

	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.84f;  buffer[i++] =  0.0f;

	buffer[i++] =  1.0f; buffer[i++] = -1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.84f;  buffer[i++] =  0.0f;

	buffer[i++] = -1.0f; buffer[i++] = -1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  0.84f;  buffer[i++] =  0.0f;

	// Back - White
	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;

	buffer[i++] = -1.0f; buffer[i++] =  1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;

	buffer[i++] = -1.0f; buffer[i++] = -1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;

	buffer[i++] =  1.0f; buffer[i++] = -1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;

	// Right - Blue
	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.27f;  buffer[i++] =  0.68f;

	buffer[i++] =  1.0f; buffer[i++] =  1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.27f;  buffer[i++] =  0.68f;

	buffer[i++] =  1.0f; buffer[i++] = -1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.27f;  buffer[i++] =  0.68f;

	buffer[i++] =  1.0f; buffer[i++] = -1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.27f;  buffer[i++] =  0.68f;

	// Left - Green
	buffer[i++] = -1.0f; buffer[i++] =  1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.6f;   buffer[i++] =  0.27f;

	buffer[i++] = -1.0f; buffer[i++] =  1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.6f;   buffer[i++] =  0.27f;

	buffer[i++] = -1.0f; buffer[i++] = -1.0f;   buffer[i++] =  1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.6f;   buffer[i++] =  0.27f;

	buffer[i++] = -1.0f; buffer[i++] = -1.0f;   buffer[i++] = -1.0f;
	buffer[i++] =  0.0f; buffer[i++] =  0.6f;   buffer[i++] =  0.27f;

	// Triangle Indexes
	GLuint indexes[36];
	i = 0;

	// Top
	indexes[i++] =  0; indexes[i++] =  1; indexes[i++] =  2;
	indexes[i++] =  0; indexes[i++] =  2; indexes[i++] =  3;

	// Bottom
	indexes[i++] =  4; indexes[i++] =  5; indexes[i++] =  6;
	indexes[i++] =  4; indexes[i++] =  6; indexes[i++] =  7;

	// Front
	indexes[i++] =  8; indexes[i++] =  9; indexes[i++] = 10;
	indexes[i++] =  8; indexes[i++] = 10; indexes[i++] = 11;

	// Back
	indexes[i++] = 12; indexes[i++] = 13; indexes[i++] = 14;
	indexes[i++] = 12; indexes[i++] = 14; indexes[i++] = 15;

	// Right
	indexes[i++] = 16; indexes[i++] = 17; indexes[i++] = 18;
	indexes[i++] = 16; indexes[i++] = 18; indexes[i++] = 19;

	// Left
	indexes[i++] = 20; indexes[i++] = 21; indexes[i++] = 22;
	indexes[i++] = 20; indexes[i++] = 22; indexes[i++] = 23;


    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint program = loadProgram("./shader/vert.glsl", NULL, NULL, NULL, "./shader/frag.glsl");

	// Vertex Array Objects (VAO)
	GLuint vao = 0;
	
	// Vertex Buffer Objects (VBO)
	GLuint vbo = 0;

	// Element Buffer Objects (EBO)
	GLuint ebo = 0;

	// ----------------------------------------
	// Triangle
	// ----------------------------------------

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind VAO, VBO & EBO
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, 144 * sizeof(GLfloat), buffer, GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indexes, GL_STATIC_DRAW);

	// Get Position Attribute location (must match name in shader)
	GLuint posLoc = glGetAttribLocation(program, "vert_Position");

	// Get Colour Attribute location (must match name in shader)
	GLuint colLoc = glGetAttribLocation(program, "vert_Colour");

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(colLoc);

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Use Program
	glUseProgram(program);

	// ----------------------------------------
	// Model Matrix
	float modelMatrix[16];
	translate(0.5f, 0.5f, 0.5f, modelMatrix);

    /*for (int i = 0; i < sizeof(modelMatrix); i++) {
        cout <<modelMatrix[i]<<",";
    }*/

	// Get Model Matrix location
	GLint modelLoc = glGetUniformLocation(program, "u_Model");

	// Copy Rotation Matrix to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix);
	// ----------------------------------------

	// ----------------------------------------
	// View Matrix
	float viewMatrix[16];
	float viewPosition[3] = { 3.0f,  3.0f,  5.0f};
	float viewUp[3]       = { 0.0f,  1.0f, 0.0f};
	float viewForward[3]  = { 0.0f, -1.0f, -1.0f};

//	 float viewPosition[3] = { 0.0f,  1.0f,  0.2f};
//	 float viewUp[3]       = { 0.0f,  0.1f, -1.0f};
//	 float viewForward[3]  = { 0.0f, -1.0f, -0.1f};

//	 float viewPosition[3] = { 1.0f,  0.0f,  1.0f};
//	 float viewUp[3]       = { 0.0f,  1.0f,  0.0f};
//	 float viewForward[3]  = { -0.5f,  0.0f, -1.0f};

	normalize(viewUp, viewUp); //  归一化
	normalize(viewForward, viewForward);

	// identity(viewMatrix);
	view(viewPosition, viewForward, viewUp, viewMatrix);

	// Get View Matrix location
	GLint viewLoc = glGetUniformLocation(program, "u_View");

	// Copy Rotation Matrix to Shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMatrix);
	// ----------------------------------------

	// ----------------------------------------
	// Projection Matrix
	float projectionMatrix[16];
	// identity(projectionMatrix);
	perspective(1.0f, 67.0f * M_PI / 180.0f, 0.2f, 10.0f, projectionMatrix);

	// Get Projection Matrix location
	GLint projectionLoc = glGetUniformLocation(program, "u_Projection");

	// Copy Rotation Matrix to Shader
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projectionMatrix);
	// ----------------------------------------

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to green
		glClearColor(0.f, 0.0f, 0.f, 0.f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use Program
		glUseProgram(program);

		 // ----------------------------------------
//		  Rotation Matrix - X
		 float rotation[16];

		 // Create Rotation Matrix
		 rotateX(glfwGetTime(), rotation);

		 // Get Model Matrix location
		 GLint modelLoc = glGetUniformLocation(program, "u_Model");

		 // Copy Rotation Matrix to Shader
		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotation);
		 // ----------------------------------------

		// // ----------------------------------------
//		 // Rotation Matrix - Y
//		 float rotation[16];
//
//		 // Create Rotation Matrix
//		 rotateY(glfwGetTime(), rotation);
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotation);
		// // ----------------------------------------

		// // ----------------------------------------
//		 // Rotation Matrix - Z
//		 float rotation[16];
//
//		 // Create Rotation Matrix
//		 rotateZ(glfwGetTime(), rotation);
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotation);
		// // ----------------------------------------

		// // ----------------------------------------
//		 // Rotation Matrix - (rx,ry,rz)
//		 float rotation[16];
//
//		 // Create Rotation Matrix
//		 rotate(glfwGetTime(), 1.0f, 1.0f, 1.0f, rotation);
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotation);
		// // ----------------------------------------

		// // ----------------------------------------
//		 // Translation Matrix
//		 float translation[16];
//
//		 // Create Translation Matrix
//		 translate(0.5 * sin(glfwGetTime()), 0.5 * cos(glfwGetTime()), 0.0f, translation);
//
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, translation);
		// // ----------------------------------------

		// // ----------------------------------------
//		 // Rotation - Translation Matrix
//		 float translation[16];
//		 float rotation[16];
//		 float model[16];
//
//		 // Create Translation Matrix
//		 translate(0.0, -0.577f, 0.0, translation);
//		 // translate(0.0, -2.0f, 0.0, translation);
//
//		 // Create Rotation Matrix
//		 rotateZ(glfwGetTime(), rotation);
//
//		 // Multiply Translation Matrix by Rotation Matrix
//		 multiply44(rotation, translation, model);
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
		// // ----------------------------------------

		// // ----------------------------------------
//		 // Translation - Rotation Matrix
//		 float translation[16];
//		 float rotation[16];
//		 float model[16];
//
//		 // Create Translation Matrix
//		 translate(0.0, -0.577f, 0.0, translation);
//		 // translate(0.0, -2.0f, 0.0, translation);
//
//		 // Create Rotation Matrix
//		 rotateZ(glfwGetTime(), rotation);
//
//		 // Multiply Translation Matrix by Rotation Matrix
//		 multiply44(translation, rotation, model);
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
		// // ----------------------------------------


		// Bind Vertex Array Object
		glBindVertexArray(vao);


		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

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


