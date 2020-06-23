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


glm::vec3 lightPos(-80.0f,100.0f,50.0f);
glm::vec3 lightEnv(0.3f,0.3f,0.3f);

Camera *camera = new Camera(glm::vec3(0.0f, 5.0f, 30.0f),glm::radians(-7.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));//(0.0f, 0.0f, -1.0f)

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
    GLFWwindow *window = createWindow(600, 600, "project4-volcanic eruption", 3, 2);
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
    Model volcano_model("res/model/volcano_sleep.obj");
    float Scale=1.5f;//model size


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
	// Particle vertex position
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

//	GLuint programParticle = Shade("./shader/particle.vert.glsl", "./shader/particle.frag.glsl").ID; //todo
    Shade * programParticle =new Shade("./shader/particle.vert.glsl", "./shader/particle.frag.glsl"); //todo

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //reflection framebuffer and depth color render target
    GLuint fbo;
    GLuint depthTex;
    GLuint colorTex;

    glGenFramebuffers(1,&fbo);
    glGenTextures(1,&depthTex);
    glGenTextures(1,&colorTex);

    glBindTexture(GL_TEXTURE_2D,colorTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,1024,1024,0,GL_RGBA,GL_UNSIGNED_BYTE,0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,depthTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,1024,1024,0,GL_DEPTH_COMPONENT,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLenum drawBuffer=GL_COLOR_ATTACHMENT0;

    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthTex,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,colorTex,0);
    glDrawBuffers(1,&drawBuffer);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
    {
        cout<<"fbo create error!"<<endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);

    //water shader
    auto waterProgram = Shade("./shader/water.vert", "./shader/water.frag"); //todo
    //water plane geometry data
    vector<Vertex> waterPlaneData={
            {{-100,0,-100},{0,1,0},{0,0}},
            {{100,0,-100},{0,1,0},{10,0}},
            {{100,0,100},{0,1,0},{10,10}},
            {{-100,0,100},{0,1,0},{0,10}},
    };

    vector<unsigned int> waterIndices={0,1,2,0,2,3};

    Mesh water=Mesh(waterPlaneData,waterIndices,{});

	lastFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        //update particles
        glm::vec3 CameraPosition = camera->Position;

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
            ParticlesContainer[particleIndex].r = 255;
            ParticlesContainer[particleIndex].g = rand()%(256-128)+128;
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

                    if(p.pos.y<0)
                    {
                        p.life=-1;
                    }
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

        glBindVertexArray(VertexArrayID);
        // 粒子的顶点坐标
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
        glBindVertexArray(0);


        //save old viewport
        int oldViewport[4];
        glGetIntegerv(GL_VIEWPORT,oldViewport);
        //render water reflection
        glBindFramebuffer(GL_FRAMEBUFFER,fbo);
        glViewport(0,0,1024,1024);
        glClearColor(0,0,0,0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //calculate reflect camera parameters
        glm::vec3 reflectScale={1,-1,1};
        glm::mat4 reflectView=glm::lookAt(camera->Position*reflectScale,
                (camera->Forward+camera->Position)*reflectScale,
                camera->Up*reflectScale
        );

        //enabel clip distance,clip mesh under water surface
        glEnable(GL_CLIP_DISTANCE0);
        modelProgram->use();
        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::translate(modelMatrix,  glm::vec3( 0.0f,  -1.5f,  -3.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(Scale));

        glm::mat4 projectionMatrix(1.0f);
        projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

        auto reflectCameraViewProjection=projectionMatrix*reflectView;

        glDisable(GL_BLEND);
        // matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(modelProgram->ID,"u_ModelMat"),1,GL_FALSE,glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(modelProgram->ID,"u_ViewMat"),1,GL_FALSE,glm::value_ptr(reflectView));
        glUniformMatrix4fv(glGetUniformLocation(modelProgram->ID,"u_ProjectionMat"),1,GL_FALSE,glm::value_ptr(projectionMatrix));
        glUniform4f(glGetUniformLocation(modelProgram->ID,"light_postion"), lightPos.x,lightPos.y,lightPos.z,0.0f);
        glUniform4f(glGetUniformLocation(modelProgram->ID,"u_camera_Postion"), camera->Position.x,camera->Position.y,camera->Position.z,0.0f);

        //render volcano mesh to reflection render target
        volcano_model.Draw(modelProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);


//        glUseProgram(programParticle->ID);
        programParticle->use();

        //开启混合
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glUseProgram(programParticle->ID);
        programParticle->use();



        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, particleTexture);

        glUniform1i(glGetUniformLocation(programParticle->ID, "FrameTexture"), 0);

        glm::mat4 ViewProjectionMatrix = projectionMatrix * reflectView;
        // 摄像头的右方向
        glUniform3f(glGetUniformLocation(programParticle->ID, "CameraRight_worldspace"), reflectView[0][0], reflectView[1][0], reflectView[2][0]);
        glUniform3f(glGetUniformLocation(programParticle->ID, "CameraUp_worldspace"), reflectView[0][1], reflectView[1][1], reflectView[2][1]);
        glUniformMatrix4fv(glGetUniformLocation(programParticle->ID, "VP"), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);


        //render particles to reflection render target
        glBindVertexArray(VertexArrayID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glDisable(GL_CLIP_DISTANCE0);
        //render scene to back buffer
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glViewport(oldViewport[0],oldViewport[1],oldViewport[2],oldViewport[3]);
        glDisable(GL_BLEND); //todo

        glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Z 缓冲


        modelProgram->use();
        glm::mat4 viewMatrix=glm::lookAt(camera->Position,camera->Position+camera->Forward,camera->Up);

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

        //draw water plane
        auto shader=waterProgram.ID;
        waterProgram.use();

        //bind reflection texture to render water
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,colorTex);
        glUniform1i(glGetUniformLocation(shader,"reflectionTex"),0);
        glUniformMatrix4fv(glGetUniformLocation(shader,"reflectViewProjection"),1,GL_FALSE,glm::value_ptr(reflectCameraViewProjection));


        glUniform1f(glGetUniformLocation(shader,"time"),glfwGetTime());
        glUniformMatrix4fv(glGetUniformLocation(shader,"u_ModelMat"),1,GL_FALSE,glm::value_ptr(glm::mat4(1.0)));
        glUniformMatrix4fv(glGetUniformLocation(shader,"u_ViewMat"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shader,"u_ProjectionMat"),1,GL_FALSE,glm::value_ptr(projectionMatrix));
        glUniform4f(glGetUniformLocation(shader,"light_postion"), lightPos.x,lightPos.y,lightPos.z,0.0f);
        glUniform4f(glGetUniformLocation(shader,"u_camera_Postion"), camera->Position.x,camera->Position.y,camera->Position.z,0.0f);
        water.Draw(&waterProgram);

		//draw particles

        programParticle->use();


        viewMatrix = camera->GetViewMatrix(); // camera movement

		//开启混合
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        programParticle->use();


		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, particleTexture);

		//        shader.SetInt("myTextureSampler", 0);
		glUniform1i(glGetUniformLocation(programParticle->ID, "myTextureSampler"), 0);

        ViewProjectionMatrix = projectionMatrix * viewMatrix;
		// 摄像头的右方向
		glUniform3f(glGetUniformLocation(programParticle->ID, "CameraRight_worldspace"), viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
		glUniform3f(glGetUniformLocation(programParticle->ID, "CameraUp_worldspace"), viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
		glUniformMatrix4fv(glGetUniformLocation(programParticle->ID, "VP"), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);


        glBindVertexArray(VertexArrayID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);


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
    float speed = 120.0f;
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




