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
//水星 金星 地球 火星 木星 土星 天王星//海王星
struct STAR{
        char url[128];
        float size ;
        float distance ;
        float RotationSpeed;
        float RevolutionSpeed;
};

//STAR Sun = {"./images/sunmap.jpg",          3.0f,   0.0f,   0.0f, 0.0f};
//STAR Mercury = {"./images/mercurymap.jpg",  .1f,    1.8f,   1.4f,0.87f};
//STAR Venus = {"./images/venusmap.jpg",      .3f,    2.5f,   1.3f,2.24f};

//STAR Earth = {"./images/EarthMap.jpg",      .8f,    4.0f,   1.0f,3.65f};

//STAR Earth = {"./images/earthbump1k.jpg",      .8f,    4.0f,   1.0f,3.65f};
STAR Earth = {"./images/EarthMap.jpg",      1.8f,    0.0f,   .02f,13.65f};

//STAR Mars = {"./images/mars_1k_color.jpg",  .4f,    6.5f,   0.8f,6.86f};
//STAR Jupiter = {"./images/jupitermap.jpg",  1.5f,   8.0f,   0.4f,23.32f};
//STAR Saturn = {"./images/saturnmap.jpg",    1.0f,   10.5f,   0.3f,40.0f};
//STAR Uranus = {"./images/uranusmap.jpg",    0.8f,   13.0f,   0.2f,80.0f};
//STAR Neptune = {"./images/neptunemap.jpg",  .8f,    15.5f,   0.1f,100.0f};

void CreateSpheres_VAO(GLuint vbo,GLuint ebo,vector<glm::vec4> buffer,vector<glm::ivec3> indexes,GLuint program);


//===== stars =====
GLuint Create_VAO    ( GLuint vbo,GLuint ebo,vector<glm::vec4> buffer,vector<glm::ivec3> indexes,GLuint program);
GLuint Create_Texture(STAR star,int x,int y, int n, GLuint program);
void Rotation  (STAR star,GLuint vaoEarth,GLuint textureEarth,vector<glm::ivec3> indexes,GLuint program);

void RenderingSpheres(GLuint vao,GLuint texture,vector<glm::ivec3> indexes,GLuint program, glm::mat4 modelMatrix);
void CameraMovement(GLFWwindow *window,
                    glm::mat4 viewMatrix, glm::vec3  viewPosition, glm::vec3 viewForward, glm::vec3 viewUp,
                    GLuint program,float last );
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
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create createSphere
    createSphere(buffer, indexes,0.8f,50,50);

	// Load GLSL Program
	GLuint program  = loadProgram("./shader/texture.vert.glsl",  NULL, NULL, NULL, "./shader/texture.frag.glsl");


	// VBO EBO
	GLuint vbo = 0;
	GLuint ebo = 0;
    // texture params
	int x, y, n;

    //name：Sum 15.0f ,Mercury 2.0f,Venus 4.0f,Earth 8.0f ,Mars 4.0f,jupiter 10.0f,Saturn 10.0f,Uranus 12.0f,Neptune 8.0f

//    // -------------object Sun---------------------------
//    GLuint textureSun = Create_Texture(Sun, x,y,n,program);
//    GLuint vaoSun = Create_VAO( vbo,ebo,buffer,indexes,program);
//    // -------------object Mercury---------------------------
//    GLuint textureMercury = Create_Texture(Mercury, x,y,n,program);
//    GLuint vaoMercury = Create_VAO( vbo,ebo,buffer,indexes,program);
//    // -------------object Venus---------------------------
//    GLuint textureVenus = Create_Texture(Venus, x,y,n,program);
//    GLuint vaoVenus = Create_VAO( vbo,ebo,buffer,indexes,program);
    // -------------object Earth---------------------------
    GLuint textureEarth = Create_Texture(Earth, x,y,n,program);
    GLuint vaoEarth = Create_VAO( vbo,ebo,buffer,indexes,program);
//    // -------------object Mars---------------------------
//    GLuint textureMars = Create_Texture(Mars, x,y,n,program);
//    GLuint vaoMars = Create_VAO( vbo,ebo,buffer,indexes,program);
//    // -------------object Jupiter---------------------------
//    GLuint textureJupiter = Create_Texture(Jupiter,x,y,n,program);
//    GLuint vaoJupiter = Create_VAO(vbo,ebo,buffer,indexes,program);
//    // -------------object Saturn---------------------------
//    GLuint textureSaturn = Create_Texture(Saturn, x,y,n,program);
//    GLuint vaoSaturn = Create_VAO( vbo,ebo,buffer,indexes,program);
//    // -------------object Uranus---------------------------
//    GLuint textureUranus = Create_Texture(Uranus, x,y,n,program);
//    GLuint vaoUranus = Create_VAO( vbo,ebo,buffer,indexes,program);
//    // -------------object Neptune---------------------------
//    GLuint textureNeptune = Create_Texture(Neptune, x,y,n,program);
//    GLuint vaoNeptune = Create_VAO( vbo,ebo,buffer,indexes,program);

	// ----------------------------------------
	// View Matrix  ----camera
	// ----------------------------------------
	glm::mat4 viewMatrix(1.0f);
	glm::vec3 viewPosition(0.0f,  0.0f,  10.0f);
	glm::vec3 viewUp      (0.0f,  1.0f,  0.0f);
	glm::vec3 viewForward (0.0f,  0.0f, -1.0f);
	// Normalise Vectors
	viewUp      = glm::normalize(viewUp);
	viewForward = glm::normalize(viewForward);
	// Construct View Matrix
	viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glm::mat4 projectionMatrix(1.0f);
	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);
	// Copy Projection Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    // ----------------------------------------

    // -----------------light-----------------------啊啊

    GLuint textureMapLoc = glGetUniformLocation(program, "u_texture_Map");
//     Set Sample Texture Unit
    glUniform1i(textureMapLoc, 0);
    glUniform4f(glGetUniformLocation(program, "material.ambient"),.1f, .1f, .1f, 0.1f);
//    glUniform4f(glGetUniformLocation(program, "material.diffuse"),0.780392, 0.568627, 0.113725, 1.0);
    glUniform1i(glGetUniformLocation(program, "material.diffuse"),0);
//    glUniform1i(glGetUniformLocation(program, "material.specular"),1);
    glUniform4f(glGetUniformLocation(program, "material.specular"),1.0f, 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), 47.89743616);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), 47.89743616);



//    glUniform4f(glGetUniformLocation(program, "material.ambient"),1.0f, 1.0f, 1.0f, 1.0f);
////    glUniform4f(glGetUniformLocation(program, "material.diffuse"),0.780392, 0.568627, 0.113725, 1.0);
//    glUniform1i(glGetUniformLocation(program, "material.diffuse"),0);
////    glUniform1i(textureMapLoc,0);
//    glUniform4f(glGetUniformLocation(program, "material.specular"),1.0f, 1.0f, 1.0f, 1.0f);
//    glUniform1f(glGetUniformLocation(program, "material.shininess"), 27.89743616);




    // Get time
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
//                cout << "dt : "<< dt<<" ; ";
//
//        cout<<"%:"<< fmod( current*10,360 ) << " ; ";



// ----------------move camera------------------------ function-------
//        void CameraMovement(window, viewMatrix, viewPosition, viewForward, viewUp, program , last);
        float camera_horizontal_angle;
        float camera_vertical_angle;
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
        // camera  angle // 尝试左右转动 cemera
        if(glfwGetKey(window, GLFW_KEY_A)) {
//            viewForward.x -=  1.0f * dt;
            camera_horizontal_angle -=  (1.0f*dt );
            viewForward.x =fmod( camera_horizontal_angle,3);
            // Construct View Matrix
            viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
            // Copy View Matrix to Shader
            glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        }
        if(glfwGetKey(window, GLFW_KEY_D)) {
//             旋转 360度
//            viewForward.x +=  (1.0f*dt );
            camera_horizontal_angle +=  (1.0f*dt );
            viewForward.x =fmod( camera_horizontal_angle,360 );
//            cout <<viewForward.x <<endl;
            // Construct View Matrix
            viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
            // Copy View Matrix to Shader
            glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        }

        if(glfwGetKey(window, GLFW_KEY_W)) {
            // Move Away
//            viewForward.y +=  1.0f * dt;
            camera_vertical_angle +=  (1.0f*dt );
            viewForward.y =fmod( camera_vertical_angle,360);
            // Construct View Matrix
            viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
            // Copy View Matrix to Shader
            glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        }
        if(glfwGetKey(window, GLFW_KEY_S)) {
            // viewForward Away
//            viewForward.y -=  1.0f * dt;
            camera_vertical_angle -=  (1.0f*dt );
            viewForward.y =fmod( camera_vertical_angle,360);
            // Construct View Matrix
            viewMatrix = glm::lookAt(viewPosition, viewPosition + viewForward, viewUp);
            // Copy View Matrix to Shader
            glUniformMatrix4fv(glGetUniformLocation(program, "u_View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        }
        // ------end----------move camera------------------------ function-------


////        // -------------object Sun---------------------------
//        Rotation(Sun, vaoSun, textureSun,indexes, program );
////        // -------------object Mercury---------------------------
//        Rotation(Mercury, vaoMercury, textureMercury,indexes, program);
////        // -------------object Venus---------------------------
//        Rotation(Venus, vaoVenus, textureVenus,indexes, program);
//        // -----------------object earth-----------------------
        Rotation(Earth, vaoEarth, textureEarth,indexes, program);
////        // -------------object Mars---------------------------
//        Rotation(Mars, vaoMars, textureMars,indexes, program);
////        // -----------------object Jupiter-----------------------
//        Rotation(Jupiter, vaoJupiter, textureJupiter,indexes, program);
////        // -------------object Saturn---------------------------
//        Rotation(Saturn, vaoSaturn, textureSaturn,indexes, program);
////        // -------------object Uranus---------------------------
//        Rotation(Uranus, vaoUranus, textureUranus,indexes, program);
//        // -------------object Neptune---------------------------
////        float theta;
//        Rotation(Neptune, vaoNeptune, textureNeptune,indexes, program);



		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Delete VAO, VBO & EBO
	glDeleteVertexArrays(1, &vaoEarth);
//    glDeleteVertexArrays(1, &vaoJupyter);
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




/*
 * =================球球们=============================
 */
// =============Star================//
GLuint Create_VAO( GLuint vbo,GLuint ebo,vector<glm::vec4> buffer,vector<glm::ivec3> indexes,GLuint program){
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    CreateSpheres_VAO(vbo,ebo,buffer,indexes,program);
    return vao;
}
/*GLuint Create_Texture(STAR star,int x,int y, int n, GLuint program){
//    unsigned char *imageEarth = loadImage(star.url, x, y, n, false);
    GLuint textureEarth = loadTexture2D(star.url, x, y, n,GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE);
//    if(imageEarth == NULL) {return 0;}
//    GLuint textureEarth;
//    glGenTextures(1, &textureEarth);
//    glBindTexture(GL_TEXTURE_2D, textureEarth);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageEarth);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // No mip-mapping
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    delete[] imageEarth;
//    imageEarth = NULL;
//    glUseProgram(program);
//    GLuint textureMapLocEarth = glGetUniformLocation(program, "u_texture_Map");
//    glUniform1i(textureMapLocEarth, 0);
    return textureEarth;
}*/


GLuint Create_Texture(STAR star,int x,int y, int n, GLuint program){
    unsigned char *imageEarth = loadImage(star.url, x, y, n, false);
//    GLuint imageEarth = loadTexture2D(star.url, x, y, n,GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE);
    if(imageEarth == NULL) {return 0;}
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageEarth);

     // Generate Mipmap
     glGenerateMipmap(GL_TEXTURE_2D);

     // Configure texture
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     // Configure Texture Coordinate Wrapping
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);


//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // No mip-mapping
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] imageEarth;
    imageEarth = NULL;
    glUseProgram(program);
    GLuint textureMapLocEarth = glGetUniformLocation(program, "u_texture_Map");
    glUniform1i(textureMapLocEarth, 0);
    return texture;
}
void Rotation(STAR star, GLuint vao,GLuint texture,vector<glm::ivec3> indexes,GLuint program){

    int num_segments= 360;
    float theta;
    if (star.RevolutionSpeed == 0.0f){
        theta = 0;
    }else{
        theta = 2.0f * M_PI  / float(num_segments);
        theta = theta * glfwGetTime()*300* (1/star.RevolutionSpeed);
    }
    float revolution_x= star.distance * cosf(theta);
    float revolution_z= star.distance * sinf(theta);

    float Rotation_theta = (float)(glfwGetTime()*star.RotationSpeed *10);

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),  glm::vec3(revolution_x, 0.0f, revolution_z)) *
                            glm::rotate(   glm::mat4(1.0f), Rotation_theta , glm::vec3(0.0f, 1.0f, 0.0f))*
                            glm::scale(glm::mat4(1.0f), glm::vec3(star.size,star.size,star.size));
    RenderingSpheres(vao,texture,indexes,program,modelMatrix);
}



/*
 *================= internal function =======================
 */
void CreateSpheres_VAO(GLuint vbo,GLuint ebo,vector<glm::vec4> buffer,vector<glm::ivec3> indexes,GLuint program){
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    // Bind VAO, VBO & EBO

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Load Vertex Data
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    // Load Element Data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);
    // Get Position Attribute location (must match name in shader)
    GLuint posLoc = glGetAttribLocation(program, "vert_Position");
    // Get Normal Attribute location (must match name in shader)
    GLuint norLoc= glGetAttribLocation(program, "vert_Normal");
    // Get Texture Attribute location (must match name in shader)
    GLuint texLoc = glGetAttribLocation(program, "vert_UV");
    // Set Vertex Attribute Pointers
    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));
    // Enable Vertex Attribute Arrays
    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(norLoc);
    glEnableVertexAttribArray(texLoc);

    // Unbind VAO, VBO & EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void RenderingSpheres(GLuint vao,GLuint texture,vector<glm::ivec3> indexes,GLuint program, glm::mat4 modelMatrix){
    // using texture, vao, index to  rendering  //
    glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

}

/*
 *================= camera movement not working....=======================
 */
/*

void CameraMovement(GLFWwindow *window,
                    glm::mat4 viewMatrix, glm::vec3  viewPosition, glm::vec3 viewForward, glm::vec3 viewUp,
                    GLuint program,float last ){
    float current = glfwGetTime();
    float dt = current - last;
    last = current;
    // ----------------move camera------------------------ function-------
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


    // ------end----------move camera------------------------ function-------

}

*/
