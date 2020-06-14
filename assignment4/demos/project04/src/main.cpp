/*
 *  Assignment 3 , 159.709, 2020 S1
 *  Family Name: JIANG , Given Name: TAO , Student ID:20004769,
 *  OBJ Model Loader:
 *      Camera angle control: Mouse move
 *      Camera movement control: A(left); D(right); W(forward); S(back); Q(rise); E(sink);
 *      Quit: ESC
 *
 *  The model aviable to load "capsule.obj" and "muro.obj"
 *  The model params:
 *      string directory    : .obj source directory
 *      string model_name   : .obj filename
 *      GLuint shadeID      :  shader program
 *      float Scale         :  resize of the model
 *      float Pos_y         :  position of the model
 *
 *  Due to extensive kinds of obj document formats,
 *  it is currently only applicable to "capsule.obj" and "mura.obj".
 *  The model loading function will be continuously improved in the future.
 *
 * */


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
#include "stb_image.h"
#include <FileSystem>
#include <Camera.h>

#include <Model.h>

using namespace std;

// --------------------------------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------------------------------

// Called on Error Event
void onError(int error, const char *description);
void onWindowClose(GLFWwindow *window);
void onFramebufferSize(GLFWwindow *window, int width, int height);

float speed = 5.0f;
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::radians(15.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));
// ----- mouse function-------//
float lastX,lastY;
bool firstMouse = true;
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ----- mouse function-------//

// --------------------------------------- -------//
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

// 粒子
struct Particle {
    glm::vec3 pos, speed;
    unsigned char r, g, b, a; // 颜色
    float size, angle, weight;
    float life; // 粒子的剩余生命，小于0表示消亡.
    float cameradistance; // *Squared* 距离摄像头的具体， 如果 dead : -1.0f

    bool operator<(const Particle& that) const {
        // 逆序排序， 远的粒子排在前面
        return this->cameradistance > that.cameradistance;
    }
};

const int MaxParticles = 1000; //最大粒子数
//const int MaxParticles = 200; //最大粒子数
const float spread = 3.0f; //粒子扩散程度
const float life = 5.0; //粒子的存活时间
Particle ParticlesContainer[MaxParticles];
int LastUsedParticle = 0;

// 在粒子数组中，找到生命消亡的粒子
int FindUnusedParticle() {
    for (int i = LastUsedParticle; i<MaxParticles; i++) {
        if (ParticlesContainer[i].life < 0) {
            LastUsedParticle = i;
            return i;
        }
    }
    for (int i = 0; i<LastUsedParticle; i++) {
        if (ParticlesContainer[i].life < 0) {
            LastUsedParticle = i;
            return i;
        }
    }
    return 0;
}

// 根据cameradistance给粒子排序
void SortParticles() {
    std::sort(&ParticlesContainer[0], &ParticlesContainer[MaxParticles]);
}

int main() {
	// Set Error Callback
	glfwSetErrorCallback(onError);

	// Initialise GLFW
	if (!glfwInit()) {
		// Return Error
		return 1;
	}

	// Create Window
	GLFWwindow *window = createWindow(600, 600, "OBJ model loader", 3, 2);

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
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//turn off mouse

    // ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	// Load GLSL Program
	GLuint program  = loadProgram("./shader/texture.vert.glsl",  NULL, NULL, NULL, "./shader/texture.frag.glsl");

//    Model model("res/model/","capsule.obj",program , 0.5f,0);
//    Model model("res/volcano_sleep_obj/","volcano_sleep.obj",program,1.0f,-3);




    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static GLfloat* g_particule_position_size_data = new GLfloat[MaxParticles * 4];
    static GLubyte* g_particule_color_data = new GLubyte[MaxParticles * 4];
    for (int i = 0; i<MaxParticles; i++)
    {
        ParticlesContainer[i].life = -1.0f;
        ParticlesContainer[i].cameradistance = -1.0f;
    }

    int x,y,n;
//    GLuint particleTexture = Texture::LoadTextureFromFile("res/texture/xuehua.png");
    GLuint particleTexture= loadTexture2D("res/volcano_sleep_obj/xuehua.png",x,y,n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
    // 粒子顶点位置
    static const GLfloat g_vertex_buffer_data[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
    };

    //  粒子的顶点坐标 （每个粒子都一样）
    GLuint billboard_vertex_buffer;
    glGenBuffers(1, &billboard_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    //  粒子的位置和大小
    GLuint particles_position_buffer;
    glGenBuffers(1, &particles_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);//初始化为NULL，后续根据粒子的属性，进行填充

    //  包含了粒子的 颜色
    GLuint particles_color_buffer;
    glGenBuffers(1, &particles_color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);//初始化为NULL，后续根据粒子的属性，进行填充

    // 开启深度测试
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint programParticle  = loadProgram("./shader/particle.vert.glsl",  NULL, NULL, NULL, "./shader/particle.frag.glsl");





    // ----------------------------------------
	// Use Program
    glUseProgram(program);
    glm::mat4 modelMatrix(1.0f);
    glm::mat4 viewMatrix(1.0f);
    glm::mat4 projectionMatrix(1.0f);
    projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
    lastFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to dark grey
		glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
		// glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use Program
		/*glUseProgram(program);

        viewMatrix = camera->GetViewMatrix(); // camera movement

        float Rotation_theta  = 0;
        modelMatrix = glm::translate(glm::mat4(1.0f),  glm::vec3(0, model.POS_y, 0)) *
                      glm::rotate(   glm::mat4(1.0f), Rotation_theta , glm::vec3(0.0f, 1.0f, 0.0f))*
                      glm::scale(glm::mat4(1.0f),glm::vec3(model.SCALE));


        glUniformMatrix4fv(glGetUniformLocation(program,"u_Model"),1,GL_FALSE,glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program,"u_View"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program,"u_Projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));


        for (int i = 0; i < model.nodes.size(); i++) {
            model.Draw(model.nodes[i]);
        }
        // Set active Texture Unit 0
        glActiveTexture(GL_TEXTURE0);

        // Unbind Texture Map
        glBindTexture(GL_TEXTURE_2D, 0);
*/




/*----------------------------------------------------*/
//        projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

//        glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 ProjectionMatrix = projectionMatrix;
        glm::mat4 ViewMatrix =viewMatrix;
        glm::vec3 CameraPosition = camera->Position;
        glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

        // 在每一帧中计算出新的deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // 消亡多少粒子，产生多少粒子
        int newparticles = deltaTime / life * MaxParticles;
        for (int i = 0; i<newparticles; i++) {
            int particleIndex = FindUnusedParticle();
            ParticlesContainer[particleIndex].life = life;
            ParticlesContainer[particleIndex].pos = glm::vec3(0, 0, -20.0f); //粒子起点
            glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f); //主要方向
            //产生随机的方向偏差
            glm::vec3 randomdir = glm::vec3(
                    (rand() % 2000 - 1000.0f) / 1000.0f, //[-1,1]
                    (rand() % 2000 - 1000.0f) / 1000.0f,
                    (rand() % 2000 - 1000.0f) / 1000.0f
            );

            ParticlesContainer[particleIndex].speed = maindir + randomdir * spread;

            // 产生随机的颜色、透明度、大小
            ParticlesContainer[particleIndex].r = rand() % 256;
            ParticlesContainer[particleIndex].g = rand() % 256;
            ParticlesContainer[particleIndex].b = rand() % 256;
            ParticlesContainer[particleIndex].a = (rand() % 100) + 50;
            ParticlesContainer[particleIndex].size = (rand() % 1000) / 5000.0f + 0.6f; //[0.6, 0.8]
        }
// 模拟所有的粒子
        int ParticlesCount = 0;
        for (int i = 0; i<MaxParticles; i++) {
            Particle& p = ParticlesContainer[i]; // 引用
            if (p.life > 0.0f) {
                p.life -= deltaTime;
                if (p.life > 0.0f) {
                    // 模拟简单物理效果：只有重力，没有碰撞
                    p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)deltaTime * 0.5f;
                    p.pos += p.speed * (float)deltaTime;
                    p.cameradistance = glm::length(p.pos - CameraPosition);
                    //填充数据
                    g_particule_position_size_data[4 * ParticlesCount + 0] = p.pos.x;
                    g_particule_position_size_data[4 * ParticlesCount + 1] = p.pos.y;
                    g_particule_position_size_data[4 * ParticlesCount + 2] = p.pos.z;
                    g_particule_position_size_data[4 * ParticlesCount + 3] = p.size;
                    g_particule_color_data[4 * ParticlesCount + 0] = p.r;
                    g_particule_color_data[4 * ParticlesCount + 1] = p.g;
                    g_particule_color_data[4 * ParticlesCount + 2] = p.b;
                    g_particule_color_data[4 * ParticlesCount + 3] = p.a;
                }
                else {
                    //已经消亡的粒子，在调用SortParticles()之后，会被放在数组的最后
                    p.cameradistance = -1.0f;
                }
                ParticlesCount++;
            }
        }

        SortParticles();
        glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
        glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);

        glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
        glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);

        //开启混合
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUseProgram(programParticle);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, particleTexture);
//        shader.SetInt("myTextureSampler", 0);
        glUniform1i(glGetUniformLocation(programParticle,"myTextureSampler"), 0);

        // 摄像头的右方向
//        shader.SetVec3("CameraRight_worldspace", ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
        glUniform3f(glGetUniformLocation(programParticle,"CameraRight_worldspace"), ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
        // 摄像头的上方向
        glUniform3f(glGetUniformLocation(programParticle,"CameraUp_worldspace"), ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
//        glUniformMatrix4fv(glGetUniformLocation(programParticle,"VP"), ViewProjectionMatrix);
        glUniformMatrix4fv(glGetUniformLocation(programParticle,"VP"), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);


        // 粒子的顶点坐标
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
        glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0
        );

        // 粒子的中心位置
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
        glVertexAttribPointer(
                1,
                4,                                // size : x + y + z + size = 4
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0
        );

        // 粒子的颜色
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
        glVertexAttribPointer(
                2,
                4,                                // size : r + g + b + a = 4
                GL_UNSIGNED_BYTE,
                GL_TRUE,
                0,
                (void*)0
        );

        glVertexAttribDivisor(0, 0); // 粒子顶点坐标 : 总是重用相同的 4 个顶点坐标，所以第二个参数是 0
        glVertexAttribDivisor(1, 1); // 粒子的中心位置和大小，每一个粒子不同，所以第二个参数是 1
        glVertexAttribDivisor(2, 1); // 粒子的颜色，每一个粒子不同，所以第二个参数是 1

        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);


/*
        // Set active Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Unbind Texture Map
		glBindTexture(GL_TEXTURE_2D, 0);*/

        // Swap the back and front buffers

		// Poll window events
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera->updateCameraPosition();// update camera position
    }

    // Delete VAO, VBO & EBO
//    model.DeleteBuffer();

    // Delete Program
//    glDeleteProgram(program);

    // Stop receiving events for the window and free resources; this must be
    // called from the main thread and should not be invoked from a callback
    glfwDestroyWindow(window);


    // Terminate GLFW
	glfwTerminate();

	return 0;
}


void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }

    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =speed;}
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -speed;}
    else{camera->speedZ = 0;}
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){camera->speedX =speed;}
    else if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){camera->speedX= -speed;}
    else{camera->speedX = 0;}
    if(glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS){camera->speedY =-speed;}
    else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS){camera->speedY= speed;}
    else{camera->speedY = 0;}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos){
    if (firstMouse == true){
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float deltaX, deltaY;
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    camera->ProcessMouseMovement(deltaX,deltaY);
}

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
