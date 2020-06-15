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

Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::radians(0.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));//(0.0f, 0.0f, -1.0f)


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

    float Scale=0.5f;


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

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Z 缓冲


        modelProgram->use();
        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::translate(modelMatrix,  glm::vec3( 0.0f,  -1.0f,  -2.0f));
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
    float speed = 10.0f;
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




