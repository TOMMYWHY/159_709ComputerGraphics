//
// Created by Tommy on 2020/5/20.
//


#ifndef OPENGL_DEMO_MESH_H
#define OPENGL_DEMO_MESH_H

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shade.h"


using  namespace std;

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords; // uv
//    glm::vec3 Tangent;
//    glm::vec3 Bitangent;
};

struct Texture{
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    vector<Vertex>  vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO,VBO,EBO;

    Mesh(float vertices[] );
    Mesh(vector<Vertex> vertices,vector<unsigned int> indices,vector<Texture> textures);
    ~Mesh();

    void Draw(Shade* shade);

private:
    void setupMesh();
};


#endif //OPENGL_DEMO_MESH_H
