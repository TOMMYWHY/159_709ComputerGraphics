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
#include "geometry.h"
#include "LightPoint.h"

using namespace std;

void onError(int error, const char *description);
void onWindowClose(GLFWwindow *window);
void onFramebufferSize(GLFWwindow *window, int width, int height);



glm::vec3 cubePositions[] = {
        glm::vec3( 1.5f,  0.0f,  -0.5f),
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

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::radians(15.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));

LightPoint * lightP = new LightPoint(lightPos,glm::vec3(1.0f,1.0f,1.0f));

// ----- mouse function-------//
float lastX,lastY;
bool firstMouse = true;
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ----- mouse function-------//



#if 1
int main() {
    if (!glfwInit()) {
        return 1;
    }
    GLFWwindow *window = createWindow(600, 600, "Self——learning", 3, 2);
    if (window == NULL) { std::cerr << "Error: create window or context failed." << std::endl;return 1;  }
    #if defined(_WIN32) || defined(__linux__)
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

    GLuint program  = loadProgram("./shader/vert.glsl",NULL, NULL, NULL,"./shader/frag.glsl");
    GLuint sunProgram  =loadProgram("./shader/lamp.vert.glsl",NULL, NULL, NULL, "./shader/lamp.frag.glsl");

// Vertex and Index buffers (host)
    std::vector<glm::vec4> buffer;
    std::vector<glm::ivec3> indexes;

    // Create Textured Cube
//    createTexturedCube(buffer, indexes);
    createSphere(buffer, indexes,0.8f,50,50);

    GLuint VBO = 0;
    GLuint EBO = 0;

//     GLuint VAO = Create_VAO(VBO,EBO,vertices,indices,shaderProgram);

//    GLuint VAO = vao_test(shaderProgram);
    GLuint VAO=0;
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


    GLuint posLoc = glGetAttribLocation(program, "vert_Position");
    GLuint norLoc = glGetAttribLocation(program, "vert_Normal");

//    GLuint colLoc = glGetAttribLocation(program, "vert_Color");
    GLuint texLoc = glGetAttribLocation(program, "vert_UV");

    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));

    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(norLoc);
    glEnableVertexAttribArray(texLoc);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);





    int x,y,n;
//    const char * texture_url = "images/container.png";
    const char * texture_url = "images/EarthMap.jpg";
//    const char * texture2_url = "images/container2_specular.png";
    GLuint texture = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
//    GLuint texture2 = loadTexture2D(texture2_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
//    GLuint texture2 = loadTexture2D(texture2_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);



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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

// 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
   /* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);*/

    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));



    glEnableVertexAttribArray(0); // posLoc

        cout <<"u_camera_Postion:"<<camera->Position.x <<","<< camera->Position.y <<","
        << camera->Position.z <<" ; " <<";"<<endl;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Z 缓冲

        glBindVertexArray(VAO);

        viewMatrix = camera->GetViewMatrix(); // camera movement

        for( int i = 0; i < 1; i++)
        {
            modelMatrix = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
            glUseProgram(program);


            glActiveTexture(GL_TEXTURE0);// 0 号位开启 texture
            glBindTexture(GL_TEXTURE_2D,texture);
            // matrix uniform
            glUniformMatrix4fv(glGetUniformLocation(program,"u_ModelMat"),1,GL_FALSE,glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(glGetUniformLocation(program,"u_ViewMat"),1,GL_FALSE,glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(glGetUniformLocation(program,"u_ProjectionMat"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

            glUniform4f(glGetUniformLocation(program,"u_camera_Postion"), camera->Position.x,camera->Position.y,camera->Position.z,1.0f );

            // light uniform
            glUniform4f(glGetUniformLocation(program,"objColor"), 1.0f,1.0f,1.0f,1.0f );
            glUniform4f(glGetUniformLocation(program,"ambinetColor"), 0.1f,0.1f,0.1f,0.0f ); //在没有光照面也能看到。。。


            //------------------ 点光 ----------------------------//
            glUniform4f(glGetUniformLocation(program,"lightP.pos"),lightP->Position.x,lightP->Position.y,lightP->Position.z,0.0f );
            glUniform4f(glGetUniformLocation(program,"lightP.color"), lightP->Color.x, lightP->Color.y, lightP->Color.z,1.0f );


            glActiveTexture(GL_TEXTURE0);// 0 号位开启 texture
            glBindTexture(GL_TEXTURE_2D,texture);
//            glActiveTexture(GL_TEXTURE0 + 1);// 1 号位开启 texture2
//            glBindTexture(GL_TEXTURE_2D,texture2);
            glUniform1i(glGetUniformLocation(program, "material_diffuse"), 0); // 手动设置
//            glUniform1i(glGetUniformLocation(program,"material_specular"), 1);


            glBindVertexArray(VAO);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);

        }
//        cout <<"u_camera_Postion:"<<camera->Position.x <<","<< camera->Position.y <<","<< camera->Position.x <<" ; "<<endl;

        glUseProgram(sunProgram);
        glUniformMatrix4fv(glGetUniformLocation(sunProgram,"view"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(sunProgram,"projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

        glm::mat4 lampModelMatrix = glm::translate(glm::mat4(1.0f),lightPos);
        lampModelMatrix = glm::scale(lampModelMatrix, glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(sunProgram,"model"),1,GL_FALSE,glm::value_ptr(lampModelMatrix));

        glBindVertexArray(lightVAO);
        glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);

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

    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =1.0f;}
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -1.0f;}
    else{camera->speedZ = 0;}
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){camera->speedX =1.0f;}
    else if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){camera->speedX= -1.0f;}
    else{camera->speedX = 0;}
    // Q下沉 E上浮
    if(glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS){camera->speedY =-1.0f;}
    else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS){camera->speedY= 1.0f;}
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




