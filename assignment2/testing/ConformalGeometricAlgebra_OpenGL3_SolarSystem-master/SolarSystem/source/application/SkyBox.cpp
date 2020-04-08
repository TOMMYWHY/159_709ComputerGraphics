#include <cmath>
#include <vector>
#include <iostream>

#include "application/SkyBox.hpp"
// #include "glimac/stb_image.h"

SkyBox::SkyBox(const GLsizei count_vertex_skybox, const ShapeVertex *verticesSkyBox) {
    //Creation du VBO
    initVBO(count_vertex_skybox, verticesSkyBox);
    //Creation du VAO
    initVAO();
};

void SkyBox::initVBO(const GLsizei count_vertex_skybox, const ShapeVertex *verticesSkyBox){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Données récupérées de la class Cube ( voir fichier cpp + hpp)
    glBufferData(GL_ARRAY_BUFFER, count_vertex_skybox * sizeof(ShapeVertex), verticesSkyBox, GL_STATIC_DRAW); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void SkyBox::initVAO(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION); GLint positionSize = 3;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);   GLint normalSize = 3;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);  GLint textureSize = 2;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        GLsizei stride = sizeof(ShapeVertex);  // le nombre d'octets séparant l'attribut pour deux sommets consécutifs.
    glVertexAttribPointer(VERTEX_ATTR_POSITION, positionSize,GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL,   normalSize,  GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE,  textureSize, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, texCoords)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  
};

GLuint SkyBox::loadTexture(std::vector<std::string> faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < faces.size(); i++) {
        std::unique_ptr<Image> texImg = loadImage(FilePath(faces[i]));
        if (texImg == NULL) {
            std::cerr << "Impossible de charger l'image dans le chemin est " << faces[i] << " car elle n'a pas été trouvée !! \n" << std::endl;
            exit(0);
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texImg->getWidth(), texImg->getHeight(), 0, GL_RGBA, GL_FLOAT, texImg->getPixels());
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureID;
};

void SkyBox::drawSkyBox(const TexSkyBox &skyBoxTexture, const GLuint &cubeMapTexture, float ratio_h_w, glm::mat4 VMatrix) {
    glBindVertexArray(vao);
    glm::mat4 MVMatrix, ProjMatrix, MVPMatrix, NormalMatrix;
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
    skyBoxTexture.m_Program.use();

    ProjMatrix = glm::perspective(glm::radians(70.f), ratio_h_w, 0.1f, 500.f);
    MVMatrix = glm::mat4(glm::mat3(VMatrix)); // Remove translation from the MV
    MVPMatrix = ProjMatrix * MVMatrix;
    glUniformMatrix4fv(skyBoxTexture.uMVP, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glBindVertexArray(0);
};