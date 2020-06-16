//
//  main.cpp
//  opengl_test
//
//  Created by Tommy on 2020/4/13.
//  Copyright © 2020 Tommy. All rights reserved.
//

#include <iostream>
//#include <glad/glad.h>
//#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"
#include <cmath>
#include <image.h>
#include <Camera.h>
#include <vector>
#include <Mesh.h>
#include <Model.h>
#include "Shade.h"
#include "geometry.h"
//

void onError(int error, const char *description);
void onWindowClose(GLFWwindow *window);
void onFramebufferSize(GLFWwindow *window, int width, int height);

float screen_width = 1280.0f;
float screen_height = 720.0f;


glm::vec3 lightPos(8.0f,15.0f,5.0f);

Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 15.0f),glm::radians(0.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));//(0.0f, 0.0f, -1.0f)

																																// ----- sky box-------//
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

const int MaxParticles = 500; //最大粒子数
//const int MaxParticles = 200; //最大粒子数
const float spread = 1.5f; //粒子扩散程度
const float life = 7.0; //粒子的存活时间
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


// ----- mouse function-------//
float lastX,lastY;
bool firstMouse = true;
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ----- mouse function-------//



#if 1
int main(int argc, char* argv[]) {
    if (!glfwInit()) {
        return 1;
    }
    GLFWwindow *window = createWindow(600, 600, "project4", 3, 2);
    if (window == NULL) { std::cerr << "Error: create window or context failed." << std::endl;return 1;  }
    #if defined(_WIN32) || defined(__linux__ )
        if (glewInit() != GLEW_OK) {
            // Return Error
            return 1;
        }
    #endif
   glfwSetFramebufferSizeCallback(window, onFramebufferSize);

    glfwSetWindowCloseCallback(window, onWindowClose);
   glfwSetCursorPosCallback(window,mouse_callback);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//turn off mouse

    // ----------------------------------------
    glEnable(GL_DEPTH_TEST); //  Z 缓冲
//    glDepthFunc(GL_LEQUAL);
    /*glEnable(GL_CULL_FACE); // todo
    glCullFace(GL_FRONT); */
    // ----------------------------------------

    Shade * modelProgram = new Shade("./shader/vert.glsl","./shader/frag.glsl");
//    GLuint shaderProgram  = loadProgram("./shader/vert.glsl",  NULL, NULL, NULL, "./shader/frag.glsl");
//    Shade * lampShade =new Shade("./shader/lamp.vert.glsl", "./shader/lamp.frag.glsl");


    Model volcano_model("res/model/volcano_sleep.obj");
    float Scale=1.5f;

//	GLuint program = Shade("./shader/texture.vert.glsl", "./shader/texture.frag.glsl").ID;
//	GLuint skyboxProgram = Shade("./shader/skybox.vert.glsl", "./shader/skybox.frag.glsl").ID;

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

	int x, y, n;
	GLuint particleTexture = loadTexture2D("./images/flare.png", x, y, n, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	GLuint pt1 = loadTexture2D("./images/1.png", x, y, n, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	GLuint pt2 = loadTexture2D("./images/2.png", x, y, n, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	GLuint pt3 = loadTexture2D("./images/3.png", x, y, n, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

	vector<GLuint> pts={pt1,pt2,pt3};
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

	GLuint programParticle = Shade("./shader/particle.vert.glsl", "./shader/particle.frag.glsl").ID;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


// ================Matrix======================//
   /* glm::mat4 modelMatrix(1.0f);
    glm::mat4 viewMatrix(1.0f);
    glm::mat4 projectionMatrix(1.0f);
//    modelMatrix =  glm::rotate(modelMatrix,glm::radians(-45.0f),glm::vec3(1,0,1.0f));
//    viewMatrix = camera->GetViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);*/


    // ----------------------- 光源 ------------------------------//
/*    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0); // posLoc

//        cout <<"u_camera_Postion:"<<camera->Position.x <<","<< camera->Position.y <<","
//        << camera->Position.z <<" ; " <<";"<<endl;*/


	lastFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

		glDisable(GL_BLEND); //todo

        glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Z 缓冲


        modelProgram->use();
        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::translate(modelMatrix,  glm::vec3( 0.0f,  -1.5f,  -3.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(Scale));

        glm::mat4 projectionMatrix(1.0f);
        projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewMatrix(1.0f);
        viewMatrix = camera->GetViewMatrix(); // camera movement


        // matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(modelProgram->ID,"u_ModelMat"),1,GL_FALSE,glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(modelProgram->ID,"u_ViewMat"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(modelProgram->ID,"u_ProjectionMat"),1,GL_FALSE,glm::value_ptr(projectionMatrix));
        glUniform4f(glGetUniformLocation(modelProgram->ID,"light_postion"), lightPos.x,lightPos.y,lightPos.z,0.0f);
        glUniform4f(glGetUniformLocation(modelProgram->ID,"u_camera_Postion"), camera->Position.x,camera->Position.y,camera->Position.z,0.0f);
        volcano_model.Draw(modelProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);


		//draw snow flakes
        glBindVertexArray(VertexArrayID);

		glUseProgram(programParticle);

		viewMatrix = camera->GetViewMatrix(); // camera movement

//        glm::mat4 ProjectionMatrix = projectionMatrix;
//        glm::mat4 ViewMatrix =viewMatrix;
		glm::vec3 CameraPosition = camera->Position;
//        glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
		glm::mat4 ViewProjectionMatrix = projectionMatrix * viewMatrix;

		// 在每一帧中计算出新的deltaTime
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// 消亡多少粒子，产生多少粒子
		int newparticles = deltaTime / life * MaxParticles;
		for (int i = 0; i<newparticles; i++) {
			int particleIndex = FindUnusedParticle();
			ParticlesContainer[particleIndex].life = life;
			ParticlesContainer[particleIndex].pos = glm::vec3(0, 0.45, -3.0f); //粒子起点
			glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f); //主要方向
															  //产生随机的方向偏差
			glm::vec3 randomdir = glm::vec3(
				(rand() % 2000 - 1000.0f) / 1000.0f, //[-1,1]
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
			);

			ParticlesContainer[particleIndex].speed = maindir + randomdir * spread;

			// 产生随机的颜色、透明度、大小
//			ParticlesContainer[particleIndex].r = rand() % 256;
			ParticlesContainer[particleIndex].r = 255;
//			ParticlesContainer[particleIndex].g = rand() % 256;
			ParticlesContainer[particleIndex].g = rand()%(256-128)+128;
//			ParticlesContainer[particleIndex].b = rand() % 256;
			ParticlesContainer[particleIndex].b = 0;
			ParticlesContainer[particleIndex].a = (rand() % 100) + 50;
			ParticlesContainer[particleIndex].size = (rand() % 1000) / 5000.0f + 0.3f; //[0.6, 0.8]
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
		glBindTexture(GL_TEXTURE_2D, pts[0]);

		//        shader.SetInt("myTextureSampler", 0);
		glUniform1i(glGetUniformLocation(programParticle, "myTextureSampler"), 0);

		// 摄像头的右方向
		glUniform3f(glGetUniformLocation(programParticle, "CameraRight_worldspace"), viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
		glUniform3f(glGetUniformLocation(programParticle, "CameraUp_worldspace"), viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
		glUniformMatrix4fv(glGetUniformLocation(programParticle, "VP"), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

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



        /**/
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();

        camera->updateCameraPosition();// update camera position

    }
    glfwTerminate();
    return 0;
}
#endif



//=========================================================================
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
    float speed = 30.0f;
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =speed;}
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -speed;}
    else{camera->speedZ = 0;}
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){camera->speedX =speed;}
    else if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){camera->speedX= -speed;}
    else{camera->speedX = 0;}
    // Q下沉 E上浮
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

//=========================================================================

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




