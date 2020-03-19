// System Headers
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

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

using namespace std;
vector<float> land_vertex_data();
vector<float> land_color_data();
vector<int> land_index_data();

void flag_vertex_data(vector<float> &vertex);
vector<float> flag_color_data(vector<float> &vertex);

vector<float> small_cylinder_vertex_data();
vector<float> small_cylinder_color_data();
vector<int> small_cylinder_index_data();

vector<float> cylinder_vertex_data();
vector<float> cylinder_color_data();
vector<int> cylinder_index_data();

vector<float> sphere_vertex_data();
vector<float> sphere_color_data(vector<float> sphereVertices);
vector<int> sphere_index_data();
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

// Normalize a vector
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
void orthographic(float width, float height, float near, float far, float matrix[16]) {
	matrix[0]  = 2.0/width;  matrix[4]  = 0.0f;         matrix[8]  =  0.0f;             matrix[12] = 0.0f;
	matrix[1]  = 0.0f;       matrix[5]  = 2.0f/height;  matrix[9]  =  0.0f;             matrix[13] = 0.0f;
	matrix[2]  = 0.0f;       matrix[6]  = 0.0f;         matrix[10] = -2.0f/(far-near);  matrix[14] = -(far+near) / (far-near);
	matrix[3]  = 0.0f;       matrix[7]  = 0.0f;         matrix[11] =  0.0f;             matrix[15] = 1.0f;
}

// Create a Perspective Projection matrix
void perspective(float aspect, float fov, float near, float far, float matrix[16]) {
	// Calculate f
	float f = 1.0f / tan(fov * 0.5);

	// Create Perspective matrix
	matrix[0]  = f/aspect;  matrix[4]  = 0.0f;  matrix[8]  =  0.0f;                  matrix[12] = 0.0f;
	matrix[1]  = 0.0f;      matrix[5]  = f;     matrix[9]  =  0.0f;                  matrix[13] = 0.0f;
	matrix[2]  = 0.0f;      matrix[6]  = 0.0f;  matrix[10] = (far+near)/(near-far);  matrix[14] = (2*far*near) / (near - far);
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
	GLFWwindow *window = createWindow(600, 600, "Example 04 - Transforms", 3, 2);

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

    GLuint program = loadProgram("./shader/vert.glsl", NULL, NULL, NULL, "./shader/frag.glsl");
    // ----------------------------------------
    // Initialise OpenGL
    // ----------------------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    //===========================================//

//--------cylinder--------
    float p = 0.0, r = 0.04;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    vector<float> cylinderVertices = cylinder_vertex_data();
    vector<float> cylinderColorList =cylinder_color_data() ;
    vector<int>   cylinderIndexList = cylinder_index_data();

    GLuint cylinder_vao = 0;
    GLuint cylinder_vbo = 0;
    GLuint cylinder_ebo = 0;
    glGenVertexArrays(1, &cylinder_vao);
    glGenBuffers(1, &cylinder_vbo);
    glGenBuffers(1, &cylinder_ebo);
    glBindVertexArray(cylinder_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_ebo);
    glBufferData(GL_ARRAY_BUFFER, cylinderVertices.size()* sizeof(float) + cylinderColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, cylinderVertices.size()* sizeof(float), &cylinderVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, cylinderVertices.size()* sizeof(float), cylinderColorList.size()* sizeof(float), &cylinderColorList[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(cylinderVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinderIndexList.size()* sizeof(float), &cylinderIndexList[0], GL_STATIC_DRAW);

//--------small_cylinder--------
//    float p = 0.0, r = 0.04;
//    int i = 0, step = 6;
//    int sample_cnt =(360/step);
    vector<float> small_cylinderVertices = small_cylinder_vertex_data();
    vector<float> small_cylinderColorList =small_cylinder_color_data() ;
    vector<int>   small_cylinderIndexList = small_cylinder_index_data();

    GLuint small_cylinder_vao = 0;
    GLuint small_cylinder_vbo = 0;
    GLuint small_cylinder_ebo = 0;
    glGenVertexArrays(1, &small_cylinder_vao);
    glGenBuffers(1, &small_cylinder_vbo);
    glGenBuffers(1, &small_cylinder_ebo);
    glBindVertexArray(small_cylinder_vao);
    glBindBuffer(GL_ARRAY_BUFFER, small_cylinder_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, small_cylinder_ebo);
    glBufferData(GL_ARRAY_BUFFER, small_cylinderVertices.size()* sizeof(float) + small_cylinderColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, small_cylinderVertices.size()* sizeof(float), &small_cylinderVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, small_cylinderVertices.size()* sizeof(float), small_cylinderColorList.size()* sizeof(float), &small_cylinderColorList[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(small_cylinderVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, small_cylinderIndexList.size()* sizeof(float), &small_cylinderIndexList[0], GL_STATIC_DRAW);


    //-------------------sphere---------------//
    const int Y_SEGMENTS = 50;
    const int X_SEGMENTS = 50;
    const float radius = 0.08;
    const GLfloat  PI = 3.14159265358979323846f;
    std::vector<float> sphereVertices = sphere_vertex_data();
    std::vector<float> sphereColorList = sphere_color_data(sphereVertices);
    std::vector<int> sphereIndices = sphere_index_data();

    GLuint sphere_vao = 0;
    GLuint sphere_vbo = 0;
    GLuint sphere_ebo = 0;
    glGenVertexArrays(1, &sphere_vao);
    glGenBuffers(1, &sphere_vbo);
    glGenBuffers(1, &sphere_ebo);
    glBindVertexArray(sphere_vao);
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ebo);

    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size()* sizeof(float) + sphereColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sphereVertices.size()* sizeof(float), &sphereVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sphereVertices.size()* sizeof(float), sphereColorList.size()* sizeof(float), &sphereColorList[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sphereVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size()* sizeof(float), &sphereIndices[0], GL_STATIC_DRAW);


    //--------land_ --------
    vector<float> landVertices =land_vertex_data();
    vector<float>  landColorList =land_color_data();
    vector<int>  landIndices =land_index_data();

    GLuint land_vao = 0;
    GLuint land_vbo = 0;
    GLuint land_ebo = 0;
    glGenVertexArrays(1, &land_vao);
    glGenBuffers(1, &land_vbo);
    glGenBuffers(1, &land_ebo);
    glBindVertexArray(land_vao);
    glBindBuffer(GL_ARRAY_BUFFER, land_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, land_ebo);

    glBufferData(GL_ARRAY_BUFFER, landVertices.size()* sizeof(float) + landColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, landVertices.size()* sizeof(float), &landVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, landVertices.size()* sizeof(float), landColorList.size()* sizeof(float), &landColorList[0]);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(landVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(landIndices)* sizeof(float), &landIndices[0], GL_STATIC_DRAW);




//--------flag--------
    /*vector<float> flagVertices =flag_vertex_data();
    vector<float>  flagColorList =flag_color_data();
    vector<int>  flagIndices =flag_index_data();*/

    vector<float> flagVertices, flagColorList;
    flag_vertex_data(flagVertices);
//    cout <<flagVertices.size() <<endl;
    flagColorList = flag_color_data(flagVertices);

    GLuint flag_vao = 0;
    GLuint flag_vbo = 0;
    GLuint flag_ebo = 0;
    glGenVertexArrays(1, &flag_vao);
    glGenBuffers(1, &flag_vbo);
    glGenBuffers(1, &flag_ebo);
    glBindVertexArray(flag_vao);
    glBindBuffer(GL_ARRAY_BUFFER, flag_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flag_ebo);

    glBufferData(GL_ARRAY_BUFFER, flagVertices.size()* sizeof(float) + flagColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, flagVertices.size()* sizeof(float), &flagVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, flagVertices.size()* sizeof(float), flagColorList.size()* sizeof(float), &flagColorList[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(flagVertices.size()* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(flagIndices)* sizeof(float), &flagIndices[0], GL_STATIC_DRAW);


    //===========================================//

    // Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Use Program
	glUseProgram(program);

	// ----------------------------------------
	// Model Matrix
	float modelMatrix[16];
	translate(0.0f, 0.0f, 0.0f, modelMatrix);

	// Get Model Matrix location
	GLint modelLoc = glGetUniformLocation(program, "u_Model");

	// Copy Rotation Matrix to Shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix);
	// ----------------------------------------

	// ----------------------------------------
	// View Matrix
	float viewMatrix[16];
	float viewPosition[3] = { 0.0f,  0.0f,  5.0f};
	float viewUp[3]       = { 0.0f,  1.0f,  0.0f};
	float viewForward[3]  = { 0.0f,  0.0f, -1.0f};

//	 float viewPosition[3] = { 0.0f,  1.0f,  0.2f};
//	 float viewUp[3]       = { 0.0f,  0.1f, -1.0f};
//	 float viewForward[3]  = { 0.0f, -1.0f, -0.1f};

//	 float viewPosition[3] = { 1.0f,  0.0f,  1.0f};
//	 float viewUp[3]       = { 0.0f,  1.0f,  0.0f};
//	 float viewForward[3]  = { -0.5f,  0.0f, -1.0f};

//	 float viewPosition[3] = { 1.0f,  1.0f,  1.0f};
//	 float viewUp[3]       = { 1.0f,  1.0f,  1.0f};
//	 float viewForward[3]  = { 1.0f,  1.0f, 1.0f};

	normalize(viewUp, viewUp);
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

//		 // ----------------------------------------
//		 // Rotation Matrix - X
//		 float rotation[16];
//
//		 // Create Rotation Matrix
//		 rotateX(glfwGetTime(), rotation);
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotation);
//		 // ----------------------------------------

//		 // ----------------------------------------
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
//		 // ----------------------------------------

//		 // ----------------------------------------
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
//		 // ----------------------------------------

//		 // ----------------------------------------
//		 // Rotation Matrix - (rx,ry,rz)
//		 float rotation[16];
//
//		 // Create Rotation Matrix
//		 rotate(glfwGetTime(), 1.0f, tan(30/180.0f * M_PI), 0.0f, rotation);
//
//		 // Get Model Matrix location
//		 GLint modelLoc = glGetUniformLocation(program, "u_Model");
//
//		 // Copy Rotation Matrix to Shader
//		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotation);
//		 // ----------------------------------------

//		 // ----------------------------------------
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
//		 // ----------------------------------------

//		 // ----------------------------------------
////		  Rotation - Translation Matrix
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
//		 // ----------------------------------------

//		 // ----------------------------------------
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
//		 // ----------------------------------------

        //===================drawing========================//

        // land
        glUseProgram(program);
        glBindVertexArray(land_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);


        //cylinder
        glUseProgram(program);
        glBindVertexArray(cylinder_vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        glDrawElements(GL_TRIANGLE_FAN, 360/step, GL_UNSIGNED_INT, (GLvoid *)(0));
        glDrawElementsBaseVertex(GL_TRIANGLE_FAN, 360/step, GL_UNSIGNED_INT, (GLvoid *)(0),1);
        glBindVertexArray(0);

        glUseProgram(program);
        glBindVertexArray(small_cylinder_vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        glDrawElements(GL_TRIANGLE_FAN, 360/step, GL_UNSIGNED_INT, (GLvoid *)(0));
        glDrawElementsBaseVertex(GL_TRIANGLE_FAN, 360/step, GL_UNSIGNED_INT, (GLvoid *)(0),1);
        glBindVertexArray(0);

        // sphere
        glUseProgram(program);
//        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glBindVertexArray(sphere_vao);
        glDrawElements(GL_TRIANGLES, X_SEGMENTS*Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);




        // flag
        glUseProgram(program);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        float timeValue = glfwGetTime();
        float waving = sin(timeValue) / 2.0f + 0.5f;

        for (int i = 0; i < flagVertices.size(); i++) {
            if(i%3 ==2){
//                Buffer[i] = waving;
                flagVertices[i] = flagVertices[i+1]*sin(0.8*timeValue+0.8* flagVertices[i+1]);
//                cout <<flagVertices[i] <<" ; ";
            }
        }

        GLuint flag_vao = 0;
        GLuint flag_vbo = 0;
        GLuint flag_ebo = 0;
        glGenVertexArrays(1, &flag_vao);
        glGenBuffers(1, &flag_vbo);
        glGenBuffers(1, &flag_ebo);
        glBindVertexArray(flag_vao);
        glBindBuffer(GL_ARRAY_BUFFER, flag_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flag_ebo);
        glBufferData(GL_ARRAY_BUFFER, flagVertices.size()* sizeof(float) + flagColorList.size()* sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, flagVertices.size()* sizeof(float), &flagVertices[0]);
        glBufferSubData(GL_ARRAY_BUFFER, flagVertices.size()* sizeof(float), flagColorList.size()* sizeof(float), &flagColorList[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(flagVertices.size()* sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(flag_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6075);
        glBindVertexArray(0);







		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Delete VAO, VBO & EBO
    glDeleteVertexArrays(1, &cylinder_vao);
    glDeleteBuffers(1, &cylinder_vbo);
    glDeleteBuffers(1, &cylinder_ebo);

    glDeleteVertexArrays(1, &small_cylinder_vao);
    glDeleteBuffers(1, &small_cylinder_vbo);
    glDeleteBuffers(1, &small_cylinder_ebo);

    glDeleteVertexArrays(1, &sphere_vao);
    glDeleteBuffers(1, &sphere_vbo);
    glDeleteBuffers(1, &sphere_ebo);

    glDeleteVertexArrays(1, &flag_vao);
    glDeleteBuffers(1, &flag_vbo);
    glDeleteBuffers(1, &flag_ebo);

    glDeleteVertexArrays(1, &land_vao);
    glDeleteBuffers(1, &land_vbo);
    glDeleteBuffers(1, &land_ebo);

	// Delete Program
	glDeleteProgram(program);

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}



#if 1
//--------land--------
vector<float> land_vertex_data(){
    std::vector<float> landVertices = {
            // 第一个三角形
            0.9f, -0.9f,-0.9f, 1.0f,      // 右上
            0.9f, -0.9f, 0.8f, 1.0f,   // 右下
            -0.9f,-0.9f, 0.9f, 1.0f,    // 左下
            // 第二个三角形
            -0.9f,-0.9f, 0.9f, 1.0f,      // 左下
            0.9f, -0.9f,-0.9f, 1.0f,    // 右上
            -0.9f,-0.9f,-0.9f, 1.0f,    // 左上
    };
    return landVertices;
}
vector<float> land_color_data(){
    std::vector<float> landVertices = {
            .0,0.635,0.345,
            .0,0.935,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
            .0,0.635,0.345,
    };
    return landVertices;
}
vector<int> land_index_data(){
    vector<int>  landIndices = {
            0, 1, 5,              // 第一个三角形
            1, 2, 5               // 第二个三角形
    };
    return landIndices;
}
//--------flag--------

void flag_vertex_data(vector<float> &vertex)
{
    int const p = 50;
    float points[ p ][ p ][3];
    for(int x=0; x<p; x++)
    {
        for(int y=0; y<p; y++)
        {
            points[x][y][0]=float(((x/5.0f))+0.046f)*0.08;
            points[x][y][1]=float(((y/5.0f))-1.96)*0.056;
            points[x][y][2]=float(sin((((x/8.0f)*40.0f)/360.0f)*3.141592654*4.0f))*0.1;
        }
    }
    for( int x = 0; x < p-1; x++ )
    {
        for( int y = 0; y < p-1; y++ )
        {
            vertex.push_back(points[x][y][0]);
            vertex.push_back(points[x][y][1]);
            vertex.push_back(points[x][y][2]);

            vertex.push_back(points[x][y+1][0]);
            vertex.push_back(points[x][y+1][1]);
            vertex.push_back(points[x][y+1][2]);

            vertex.push_back(points[x+1][y+1][0]);
            vertex.push_back(points[x+1][y+1][1]);
            vertex.push_back(points[x+1][y+1][2]);

            vertex.push_back(points[x+1][y][0]);
            vertex.push_back(points[x+1][y][1]);
            vertex.push_back(points[x+1][y][2]);
        }
    }
}

vector<float> flag_color_data(vector<float> &vertex){
    std::vector<float> flagColor;
    for (int i = 0; i < vertex.size()/3; i++) {
        flagColor.push_back(0.0f);
        flagColor.push_back(0.635f);
        flagColor.push_back(0.345f);
    }
    return flagColor;
}


//--------cylinder--------
vector<float> cylinder_vertex_data(){
    float p = 0.0, r = 0.04;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    std::vector<float> cylinderVertices;
    for ( i = 0; i < sample_cnt * 2; i += 2)
    {
        p = i * step * 3.14 / 180;
        float xPos = cos(p) * r;
        float yPos = 0.5f;
        float zPos = sin(p) * r;
        cylinderVertices.push_back(xPos);
        cylinderVertices.push_back(yPos);
        cylinderVertices.push_back(zPos);
        float xPos_next = cos(p) * r;
        float yPos_next = -0.7f;
        float zPos_next = sin(p) * r;
        cylinderVertices.push_back(xPos_next);
        cylinderVertices.push_back(yPos_next);
        cylinderVertices.push_back(zPos_next);
    }
    return cylinderVertices;

}
vector<float> cylinder_color_data(){
    float p = 0.0, r = 0.04;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    std::vector<float> cylinderColorList;
    for (int i = 0; i < sample_cnt * 2; i++)
    {
        cylinderColorList.push_back(0.9f);
        cylinderColorList.push_back(0.9f);
        cylinderColorList.push_back(0.0f);
    }
    return cylinderColorList;

}
vector<int> cylinder_index_data(){
    float p = 0.0, r = 0.04;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    std::vector<int> cylinderIndexList;
    for (int i = 0; i < sample_cnt; i++)
    {
        int index = i+2;
        cylinderIndexList.push_back(index) ;
    }
    return cylinderIndexList;

}
//--------small cylinder--------
vector<float> small_cylinder_vertex_data(){
    float p = 0.0, r = 0.02;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    std::vector<float> cylinderVertices;
    for ( i = 0; i < sample_cnt * 2; i += 2)
    {
        p = i * step * 3.14 / 180;
        float xPos = cos(p) * r;
        float yPos = -0.7f;
        float zPos = sin(p) * r;
        cylinderVertices.push_back(xPos);
        cylinderVertices.push_back(yPos);
        cylinderVertices.push_back(zPos);
        float xPos_next = cos(p) * r;
        float yPos_next = -0.9f;
        float zPos_next = sin(p) * r;
        cylinderVertices.push_back(xPos_next);
        cylinderVertices.push_back(yPos_next);
        cylinderVertices.push_back(zPos_next);
    }
    return cylinderVertices;

}
vector<float> small_cylinder_color_data(){
    float p = 0.0, r = 0.02;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    std::vector<float> cylinderColorList;
    for (int i = 0; i < sample_cnt * 2; i++)
    {
        cylinderColorList.push_back(0.9f);
        cylinderColorList.push_back(0.9f);
        cylinderColorList.push_back(0.0f);
    }
    return cylinderColorList;

}
vector<int> small_cylinder_index_data(){
    float p = 0.0, r = 0.02;
    int i = 0, step = 6;
    int sample_cnt =(360/step);
    std::vector<int> cylinderIndexList;
    for (int i = 0; i < sample_cnt; i++)
    {
        int index = i+2;
        cylinderIndexList.push_back(index) ;
    }
    return cylinderIndexList;

}
//===========sphere================================//
vector<float> sphere_vertex_data(){
    const int Y_SEGMENTS = 50;
    const int X_SEGMENTS = 50;
    const float radius = 0.08;
    const GLfloat  PI = 3.14159265358979323846f;
    std::vector<float> sphereVertices;
    for (int y = 0; y <= Y_SEGMENTS; y++)
    {
        for (int x = 0; x <= X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            sphereVertices.push_back(xPos*radius);
            sphereVertices.push_back(yPos*radius+0.5f);
            sphereVertices.push_back(zPos*radius);
        }
    }
    return sphereVertices;

}
vector<float> sphere_color_data(vector<float> sphereVertices){
    std::vector<float> sphereColorList;
    for (int i = 0; i < sphereVertices.size();) {
        sphereColorList.push_back(0.9f);
        sphereColorList.push_back(0.4f);
        sphereColorList.push_back(0.2f);
        i = i+3;
    }
    return sphereColorList;

}
vector<int> sphere_index_data(){
    const int Y_SEGMENTS = 50;
    const int X_SEGMENTS = 50;
    std::vector<int> sphereIndices;
    // sphere Indices
    for (int i = 0; i < Y_SEGMENTS; i++)
    {
        for (int j = 0; j < X_SEGMENTS; j++)
        {
            sphereIndices.push_back(i * (X_SEGMENTS+1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);

            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
        }
    }
    return sphereIndices;
}
#endif