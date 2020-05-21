//
// Created by Tommy on 2020/5/20.
//

#include "Mesh.h"
#include <iostream>

Mesh::~Mesh() {

}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->setupMesh();
}

/*void Mesh::Draw(Shade *shade) {
    for (int i = 0; i <textures.size() ; i++) {
        if(textures[i].type=="texture_diffuse"){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,textures[i].id);
            glUniform1i(glGetUniformLocation(shade->ID,"material_diffuse"), 0 );
        }
        else if(textures[i].type=="texture_specular"){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,textures[i].id);
            glUniform1i(glGetUniformLocation(shade->ID,"material_specular"), 1);
        }
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT ,NULL);
//    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}*/

void Mesh::Draw(Shade* shade) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);
        glUniform1i(glGetUniformLocation(shade->ID, (name + number).c_str()), i);
        std:: cout << (name + number).c_str() <<std::endl;
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(),&vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);

   /* glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)0);//Position //todo 4
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)(3*sizeof(float)));//Normal TODO 4
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)(6*sizeof(float))); // UV todo 4*/

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));


    glBindVertexArray(0);

}

Mesh::Mesh(float *vertices) {
    this->vertices.resize(36);
    memcpy(&(this->vertices[0]),vertices,36*8* sizeof(float));
    this->setupMesh();

}
