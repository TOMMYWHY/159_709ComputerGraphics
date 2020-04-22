/*
 *  Assignment 2 , 159.709, 2020 S1
 *  Family Name: JIANG , Given Name: TAO , Student ID:20004769,
 *  Solar system:
 *  Camera angle control: Mouse move
 *  Camera movement control: A(left); D(right); W(forward); S(back); Q(rise); E(sink);
 *  Pause function control: SPACE
 *  Quit: ESC
 *
 * */



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
#include "image.h"
#include <Camera.h>
#include <vector>
#include <stb_image.h>
#include "geometry.h"

using namespace std;

void onError(int error, const char *description);
void onWindowClose(GLFWwindow *window);
void onFramebufferSize(GLFWwindow *window, int width, int height);

//水星 金星 地球 火星 木星 土星 天王星//海王星
struct STAR{
    char texture_url[128];
    char texture_bump[128];
    float size ;
    float distance ;
    float RotationSpeed; // rotation 自转
    float RevolutionSpeed; // revolution 公转
//    glm::vec3 location;
};
STAR Sun = {"./images/sunmap.tga","./images/sunmap.tga",            3.0f,   0.0f,   0.0f, 0.0f};
STAR Mercury = {"./images/mercurymap.jpg","./images/mercurybump.jpg",.1f,    3.5f,   1.4f,3.87f};
STAR Venus = {"./images/venusmap.jpg","./images/venusbump.jpg",      .3f,    4.5f,   1.3f,4.24f};
STAR Earth = {"./images/earth_nightmap.jpg","./images/earth_specular_map.jpg",      .8f,    6.0f,   1.0f,7.65f};

STAR Mars = {"./images/mars_1k_color.jpg","./images/mars_1k_color.jpg",.4f,    7.5f,   0.8f,16.86f};
STAR Jupiter = {"./images/jupitermap.jpg","./images/jupitermap.jpg", 2.5f,   11.0f,   0.4f,25.32f};
STAR Saturn = {"./images/saturnmap.jpg","./images/saturnmap.jpg",   1.0f,   16.5f,   0.3f,40.0f};
STAR Uranus = {"./images/uranusmap.jpg","./images/uranusmap.jpg",2.8f,   22.0f,   0.2f,80.0f};
STAR Neptune = {"./images/neptunemap.jpg","./images/neptunemap.jpg",   2.4f,   32.5f,   0.1f,100.0f};

STAR stars[8] = {
        Mercury,Venus,Earth,Mars,Jupiter,Saturn,Uranus,Neptune
};

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

bool is_play = true;
int timing = 0;
// ----- mouse function-------//
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 20.0f),glm::radians(0.0f),glm::radians(180.0f), glm::vec3(0.0f,  1.0f,  0.0f));
float lastX,lastY;
bool firstMouse = true;
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ----- mouse function-------//
unsigned int loadCubemap(vector<std::string> faces);

float skyboxVertices [] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

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
   glfwSetCursorPosCallback(window,mouse_callback); // mouse move function
   glfwMakeContextCurrent(window);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//turn off mouse

    // ----------------------------------------
    glEnable(GL_DEPTH_TEST); //  Z buffer
    glDepthFunc(GL_LEQUAL);
//    glEnable(GL_FRAMEBUFFER_SRGB);
    // ----------------------------------------

    GLuint program  = loadProgram("./shader/vert.glsl",NULL, NULL, NULL,"./shader/frag.glsl");
    GLuint sunProgram  =loadProgram("./shader/sun.vert.glsl",NULL, NULL, NULL, "./shader/sun.frag.glsl");
    GLuint skyboxProgram  =loadProgram("./shader/skybox.vert.glsl",NULL, NULL, NULL, "./shader/skybox.frag.glsl");

// Vertex and Index buffers
    std::vector<glm::vec4> buffer;
    std::vector<glm::ivec3> indexes;

    // Create Textured sphere
    createSphere(buffer, indexes,0.8f,100,100);

    GLuint VBO = 0;
    GLuint EBO = 0;
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

    GLuint posLoc = glGetAttribLocation(program, "vert_Position");
    GLuint norLoc = glGetAttribLocation(program, "vert_Normal");
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

    // ----------------------- texture  group------------------------------//
    stbi_set_flip_vertically_on_load(true);
    int x,y,n;
    vector<GLuint> textureIDs;
    vector<GLuint> texture_bumpIDs;
    for (int i = 0; i <  sizeof(stars)/ sizeof(stars[0]); i++) {
        GLuint texture = loadTexture2D(stars[i].texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
        GLuint texture_bump = loadTexture2D(stars[i].texture_bump, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
        textureIDs.push_back(texture);
        texture_bumpIDs.push_back(texture_bump);
    }

    // ----------------------- Sun single Light Source ------------------------------//
    const char * texture_url_sun = "./images/sunmap.tga";
    GLuint textureSun = loadTexture2D(texture_url_sun, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));
    glEnableVertexAttribArray(0); //
    glEnableVertexAttribArray(1); //
    glEnableVertexAttribArray(2); //



    // ----------------------- sky box ------------------------------//

    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    vector<std::string> faces
            {
                    "./images/right.png",
                    "./images/left.png",
                    "./images/top.png",
                    "./images/bot.png",
                    "./images/front.png",
                    "./images/back.png"
            };
    unsigned int cubemapTexture = loadCubemap(faces);


    // ================Matrix======================//
    glm::mat4 modelMatrix(1.0f);
    glm::mat4 viewMatrix(1.0f);
    glm::mat4 projectionMatrix(1.0f);
    projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Z 缓冲

        //------------------ sky box ----------------------------//
        // draw skybox as last
        glDepthMask(GL_FALSE);

        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        glUseProgram(skyboxProgram);
        viewMatrix = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
//        skyboxShader.setMat4("view", view);
        glUniformMatrix4fv(glGetUniformLocation(skyboxProgram,"view"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(skyboxProgram,"projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
        glDepthMask(GL_TRUE);

        glUseProgram(program);

        glBindVertexArray(VAO);

        viewMatrix = camera->GetViewMatrix(); // camera movement

        for( int i = 0; i <  sizeof(stars)/ sizeof(stars[0]); i++)
        {
            int num_segments= 360;
            float  theta = 2.0f * M_PI  / float(num_segments);
            if(is_play == true){
                timing ++;
            }else{
                timing = timing;
            }
            theta = theta * timing *0.05* (1/stars[i].RevolutionSpeed);
            float revolution_x= stars[i].distance * cosf(theta);
            float revolution_z= stars[i].distance * sinf(theta);
//            float revolution_y= stars[i].distance * sinf(theta);
            float Rotation_theta  = (float)(glfwGetTime()*stars[i].RotationSpeed *1);
            modelMatrix = glm::translate(glm::mat4(1.0f),  glm::vec3(revolution_x, 0, revolution_z)) *
                                    glm::rotate(   glm::mat4(1.0f), Rotation_theta , glm::vec3(0.0f, 1.0f, 0.0f))*
                                    glm::scale(glm::mat4(1.0f), glm::vec3(stars[i].size));

            glUseProgram(program);
            // matrix uniform
            glUniformMatrix4fv(glGetUniformLocation(program,"u_ModelMat"),1,GL_FALSE,glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(glGetUniformLocation(program,"u_ViewMat"),1,GL_FALSE,glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(glGetUniformLocation(program,"u_ProjectionMat"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

//            glUniform4f(glGetUniformLocation(program,"u_camera_Postion"), camera->Position.x,camera->Position.y,camera->Position.z,1.0f );

            //------------------ 点光 ----------------------------//
//            glUniform4f(glGetUniformLocation(program,"lightP.pos"),lightPos.x,lightPos.y,lightPos.z,0.0f );
//            glUniform4f(glGetUniformLocation(program,"lightP.color"), 1.0f,1.0f,1.0f,1.0f );

            glActiveTexture(GL_TEXTURE0 );// 0 号位开启 texture
            glBindTexture(GL_TEXTURE_2D,textureIDs[i]);

            glActiveTexture(GL_TEXTURE1 );// 0 号位开启 texture
            glBindTexture(GL_TEXTURE_2D,texture_bumpIDs[i]);

//            glBindTexture(GL_TEXTURE_2D,texture4);
            glUniform1i(glGetUniformLocation(program, "material_diffuse"), 0); // texture
            glUniform1i(glGetUniformLocation(program, "material_specular"), 1); // texture
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);

        }
        //------------------ SUN 光源 ----------------------------//

        glUseProgram(sunProgram);
        glUniformMatrix4fv(glGetUniformLocation(sunProgram,"u_View"),1,GL_FALSE,glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(sunProgram,"u_Projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

        glm::mat4 lampModelMatrix = glm::translate(glm::mat4(1.0f),lightPos);
        lampModelMatrix = glm::scale(lampModelMatrix, glm::vec3(Sun.size));
        glUniformMatrix4fv(glGetUniformLocation(sunProgram,"u_Model"),1,GL_FALSE,glm::value_ptr(lampModelMatrix));

        glActiveTexture(GL_TEXTURE0);// 0 号位开启 texture
        glBindTexture(GL_TEXTURE_2D,textureSun);
        glUniform1i( glGetUniformLocation(sunProgram, "textureSun"), 0);


        glBindVertexArray(lightVAO);
        glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, NULL);
        //------------------ SUN 光源 done ----------------------------//



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
//=============================skybox============================================

unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


//=========================================================================
void processInput(GLFWwindow *window){
    float Sense = 10.0f;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){glfwSetWindowShouldClose(window,true);}
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){camera->speedZ =Sense;}
    else if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){camera->speedZ= -Sense;}
    else{camera->speedZ = 0;}
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){camera->speedX =Sense;}
    else if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){camera->speedX= -Sense;}
    else{camera->speedX = 0;}
    // Q下沉 E上浮
    if(glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS){camera->speedY =-Sense;}
    else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS){camera->speedY= Sense;}
    else{camera->speedY = 0;}
    if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS){
        is_play = !is_play;
    }
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




