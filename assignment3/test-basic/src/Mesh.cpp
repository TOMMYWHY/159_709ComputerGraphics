//
// Created by Tommy on 2020/5/22.
//

#include "Mesh.h"

Mesh::~Mesh() {}


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
//    this->textures = textures;
    this->setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->setupMesh();
}



void Mesh::setupMesh() {
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
    glGenBuffers(1, &(this->EBO));
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &(this->vertices[0]), GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &(this->indices[0]), GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //position

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));//Normal
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)(3*sizeof(float)));//Normal TODO change to this style

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));// UV

    /*glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
*/
    glBindVertexArray(0);
}


void Mesh::Draw(GLuint shaderId) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string name = this->textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);
        glUniform1i(glGetUniformLocation(shaderId, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::Draw_old(GLuint shaderId) {
    for (int i = 0; i <this->textures.size() ; i++) {
        if(this->textures[i].type=="texture_diffuse"){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,this->textures[i].id);
            glUniform1i(glGetUniformLocation(shaderId,"material_diffuse"), 0 );
        }
        else if(this->textures[i].type=="texture_specular"){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,this->textures[i].id);
            glUniform1i(glGetUniformLocation(shaderId,"material_specular"), 1);
        }
    }
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(),GL_UNSIGNED_INT ,NULL);
//    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}