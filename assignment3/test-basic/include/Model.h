//
// Created by Tommy on 2020/5/23.
//

#ifndef OPENGL_START_08_MODEL_H
#define OPENGL_START_08_MODEL_H
#include <iostream>
#include <string>
#include <vector>
#include "Mesh.h"

template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

struct Node{
    string name;
    int lineStarIndex;
    int lineEndIndex;
    int face_lineStartIndex;
    int face_lineEndIndex;
    string usemtl;


};

struct Part{
    vector<glm::vec4>buffer;
    vector<glm::ivec3>indexes;
};

using namespace std;
class Model {
public:
    unsigned int VAO;

    GLuint ShadeID;
    string Directory;
    string Model_name;
    vector<Mesh> meshes;
    vector<MeshTexture> textures_loaded;
    vector<Part> parts;


    Model(string directory,string model_name,GLuint shadeID);
    ~Model();
    void loadModel();

    void setupMesh(Part pa);
    void Draw();
};


#endif //OPENGL_START_08_MODEL_H
