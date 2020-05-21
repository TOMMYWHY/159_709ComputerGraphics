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
#include "shader.h"
#include <cmath>
#include <image.h>
#include <Camera.h>
#include <vector>
#include <Mesh.h>
#include <Model.h>
#include <ObjModel.h>
#include "Shade.h"
#include "geometry.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

void onError(int error, const char *description);
void onWindowClose(GLFWwindow *window);
void onFramebufferSize(GLFWwindow *window, int width, int height);

float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
};

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

    glm::vec3 lightPos(1.0f, 1.3f, -1.0f);

//    Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f));
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::radians(15.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));
LightDirectional * lightD = new LightDirectional(
        lightPos,
        glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0),
         glm::vec3(1.0f,1.0f,1.0f));

LightPoint * lightP0 = new LightPoint(glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(1.0f,0.0f,0.0f));
LightPoint * lightP1 = new LightPoint(glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f));
LightPoint * lightP2 = new LightPoint(glm::vec3(0.0f, 0.0f, 1.0f),glm::vec3(0.0f,0.0f,1.0f));
LightPoint * lightP3 = new LightPoint(glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(1.0f,1.0f,1.0f));

LightSpot * lightS = new LightSpot(
        glm::vec3(0.0f, 5.0f, 0.0f),
         glm::vec3(glm::radians(90.0f),glm::radians(0.0f),0),
          glm::vec3(1.0f,1.0f,1.0f));
// ----- mouse function-------//
float lastX,lastY;
bool firstMouse = true;
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ----- mouse function-------//










#if 1
int main() {

//    model.loadOBJ("cube.obj", vertices, uvs, normals);

//    cout << "argv[0] : "<< argv[0]<<endl;
//    cout << "argv[0] : "<< exePath.substr( 0,exePath.find_last_of('/')) + "/model/nanosuit.obj"<<endl;

    if (!glfwInit()) {
        return 1;
    }
    GLFWwindow *window = createWindow(600, 600, "Self——learning", 3, 2);
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
    glDepthFunc(GL_LEQUAL);
    /*glEnable(GL_CULL_FACE); // todo
    glCullFace(GL_FRONT); */
    // ----------------------------------------

    Shade * shaderProgram = new Shade("./shader/vert.glsl","./shader/frag.glsl");
//    GLuint shaderProgram  = loadProgram("./shader/vert.glsl",  NULL, NULL, NULL, "./shader/frag.glsl");
    Shade * lampShade =new Shade("./shader/lamp.vert.glsl", "./shader/lamp.frag.glsl");

// Vertex and Index buffers (host)
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    ObjModel model;
    model.ObjLoader("res/model/box.obj");
    cout <<model.vSets.size() <<endl;
    for (int i = 0; i < model.vSets.size(); i++) {
        cout << model.vSets[i][0]<<","<<model.vSets[i][1] << "," << model.vSets[i][2]<<endl;
    }
    cout <<"===================="<< endl;
    cout <<model.fSets.size() <<endl;
    for (int i = 0; i < model.fSets.size(); i++) {
        cout << model.fSets[i][0]<<","<<model.fSets[i][1] << "," << model.fSets[i][2]<<","<< model.fSets[i][3] <<endl;
    }
/*
    bool res = model.loadOBJ("res/model/muro.obj",vertices,uvs,normals);
//    cout <<"vertices:" <<vertices.size()<< endl;
    for (int i = 0; i < vertices.size(); i++) {
//        cout << vertices[i].x<<","<<vertices[i].y<<vertices[i].z<<endl;
    }
*/


    std::vector<glm::vec4> buffer;
    std::vector<glm::ivec3> indexes;


    // Create Textured Cube
    createTexturedCube(buffer, indexes);

    GLuint VBO = 0;
    GLuint EBO = 0;

//     GLuint VAO = Create_VAO(VBO,EBO,vertices,indices,shaderProgram);

//    GLuint VAO = vao_test(shaderProgram);
/*    GLuint VAO=0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    GLuint posLoc = glGetAttribLocation(shaderProgram->ID, "vert_Position");
    GLuint norLoc = glGetAttribLocation(shaderProgram->ID, "vert_Normal");

//    GLuint colLoc = glGetAttribLocation(shaderProgram->ID, "vert_Color");
    GLuint texLoc = glGetAttribLocation(shaderProgram->ID, "vert_UV");

    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));

    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(norLoc);
    glEnableVertexAttribArray(texLoc);*/
//    Mesh cube(vertices);
//    Model model( exePath.substr( 0,exePath.find_last_of('/')) + "/oldMan/muro.obj");
//    Model model( "res/model/muro.obj");
//    Model model( "res/model/box.obj");




    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);





    int x,y,n;
    const char * texture_url = "images/container.png";
//    const char * texture_url = "images/EarthMap.jpg";
    const char * texture2_url = "images/container2_specular.png";
    GLuint texture = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
//    GLuint texture2 = loadTexture2D(texture2_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
    GLuint texture2 = loadTexture2D(texture2_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);



// ================Matrix======================//
    glm::mat4 modelMatrix(1.0f);
    glm::mat4 viewMatrix(1.0f);
    glm::mat4 projectionMatrix(1.0f);
//    modelMatrix =  glm::rotate(modelMatrix,glm::radians(-45.0f),glm::vec3(1,0,1.0f));
//    viewMatrix = camera->GetViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);


    // ----------------------- 光源 ------------------------------//
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
// 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
   /* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);*/

    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0); // posLoc

        cout <<"u_camera_Postion:"<<camera->Position.x <<","<< camera->Position.y <<","
        << camera->Position.z <<" ; " <<";"<<endl;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Z 缓冲

//        glBindVertexArray(VAO);

        viewMatrix = camera->GetViewMatrix(); // camera movement

        for( int i = 0; i < 1; i++)
        {
            modelMatrix = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
            shaderProgram->use();


            glActiveTexture(GL_TEXTURE0);// 0 号位开启 texture
            glBindTexture(GL_TEXTURE_2D,texture);
            // matrix uniform
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID,"u_ModelMat"),1,GL_FALSE,glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID,"u_ViewMat"),1,GL_FALSE,glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID,"u_ProjectionMat"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

            glUniform4f(glGetUniformLocation(shaderProgram->ID,"u_camera_Postion"), camera->Position.x,camera->Position.y,camera->Position.z,1.0f );

            // light uniform
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"objColor"), 1.0f,1.0f,1.0f,1.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"ambinetColor"), 0.0f,0.0f,0.0f,0.0f ); //在没有光照面也能看到。。。

            //------------------ 平行光 ----------------------------//
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightD.pos"),lightD->Position.x,lightD->Position.y,lightD->Position.z,0.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightD.color"), lightD->Color.x, lightD->Color.y, lightD->Color.z,1.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightD.dirToLight"), lightD->Direction.x, lightD->Direction.y, lightD->Direction.z,0.0f );

            //------------------ 点光 0----------------------------//
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP0.pos"),lightP0->Position.x,lightP0->Position.y,lightP0->Position.z,0.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP0.color"), lightP0->Color.x, lightP0->Color.y, lightP0->Color.z,1.0f );
//------------------ 点光 1 ----------------------------//
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP1.pos"),lightP1->Position.x,lightP1->Position.y,lightP1->Position.z,0.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP1.color"), lightP1->Color.x, lightP1->Color.y, lightP1->Color.z,1.0f );
//------------------ 点光 2----------------------------//
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP2.pos"),lightP2->Position.x,lightP2->Position.y,lightP2->Position.z,0.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP2.color"), lightP2->Color.x, lightP2->Color.y, lightP2->Color.z,1.0f );
//------------------ 点光 3----------------------------//
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP3.pos"),lightP3->Position.x,lightP3->Position.y,lightP3->Position.z,0.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightP3.color"), lightP3->Color.x, lightP3->Color.y, lightP3->Color.z,1.0f );


            //------------------  聚焦光 ----------------------------//
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightS.pos"),lightS->Position.x,lightS->Position.y,lightS->Position.z,0.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightS.color"), lightS->Color.x, lightS->Color.y, lightS->Color.z,1.0f );
            glUniform4f(glGetUniformLocation(shaderProgram->ID,"lightS.dirToLight"), lightS->Direction.x, lightS->Direction.y, lightS->Direction.z,0.0f );
            glUniform1f(glGetUniformLocation(shaderProgram->ID,"lightS.cosPhyInner"), lightS->cosPhyInner );
            glUniform1f(glGetUniformLocation(shaderProgram->ID,"lightS.cosPhyOuter"), lightS->cosPhyOuter );
            /* // 聚焦光源
             glUniform1f(glGetUniformLocation(shaderProgram->ID,"lightSpot.cosPhyInner"), light->cosPhyInner );
             glUniform1f(glGetUniformLocation(shaderProgram->ID,"lightSpot.cosPhyOuter"), light->cosPhyOuter );*/



            /*glActiveTexture(GL_TEXTURE0);// 0 号位开启 texture
            glBindTexture(GL_TEXTURE_2D,texture);
            glActiveTexture(GL_TEXTURE0 + 1);// 1 号位开启 texture2
            glBindTexture(GL_TEXTURE_2D,texture2);
            glUniform1i(glGetUniformLocation(shaderProgram->ID, "material_diffuse"), 0); // 手动设置
            glUniform1i(glGetUniformLocation(shaderProgram->ID,"material_specular"), 1);*/


           /* glBindVertexArray(VAO);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);*/

//            cube.Draw(shaderProgram);
//            model.Draw(shaderProgram);

        }
//        cout <<"u_camera_Postion:"<<camera->Position.x <<","<< camera->Position.y <<","<< camera->Position.x <<" ; "<<endl;

        lampShade->use();
        glUniformMatrix4fv(glGetUniformLocation(lampShade->ID,"view"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(lampShade->ID,"projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

        glm::mat4 lampModelMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(lightD->Position));
        lampModelMatrix = glm::scale(lampModelMatrix, glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(lampShade->ID,"model"),1,GL_FALSE,glm::value_ptr(lampModelMatrix));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);




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
    float speed = 100.0f;
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

   /*
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =1.0f;}
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -1.0f;}
    else{camera->speedZ = 0;}*/

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
//    cout<<"xpos:" <<xPos<< ", ypos:"<< yPos<<endl;
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


