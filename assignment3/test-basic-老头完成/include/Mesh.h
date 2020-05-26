//
// Created by Tommy on 2020/5/22.
//

#ifndef OPENGL_START_08_MESH_H
#define OPENGL_START_08_MESH_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;


struct Vertex {
    glm::vec3 Position; //v
    glm::vec3 Normal; //vn
    glm::vec2 TexCoords; // vn/uv
//    glm::vec3 Tangent;
//    glm::vec3 Bitangent;
};
struct MeshTexture {
    unsigned int id;
    string type; // difuss or specular
    string path;
};
class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int>indices;
    vector<MeshTexture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
    void Draw(GLuint shaderId);
    void Draw_old(GLuint shaderId);

    ~Mesh();
private:
    unsigned int VBO, EBO;
    void setupMesh();
};


#endif //OPENGL_START_08_MESH_H
