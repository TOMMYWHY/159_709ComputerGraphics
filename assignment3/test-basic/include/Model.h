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
using namespace std;
class Model {
public:
    string Directory;
    string Model_name;
    vector<Mesh> meshes;
    vector<MeshTexture> textures_loaded;


    Model(string directory,string model_name);
    ~Model();
    void loadModel();

};


#endif //OPENGL_START_08_MODEL_H
