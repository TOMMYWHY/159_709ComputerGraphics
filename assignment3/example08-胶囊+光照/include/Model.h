//
// Created by Tommy on 2020/5/22.
//

#ifndef OPENGL_START_08_MODEL_H
#define OPENGL_START_08_MODEL_H
#include <string>
#include <vector>
#include "Mesh.h"
#include <iostream>

struct Mtl{
    string mtlName;
    float Ka[3]; //环境反射
    float Kd[3]; //漫反射
    float Ks[3]; //镜反射
    GLuint texture; // kd
    GLuint texture_bump; // nv
    GLuint texture_ks; //ks
};

struct Face{
    string usemtl;
    int lineIndex;
    vector<unsigned int> indices;

};

template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

class Model {
public:

    Model(string directory,string model_name);
    ~Model();
    vector<Face> Faces;
    string Model_name;
    vector<Mesh> meshes;
    string Directory;
    vector<MeshTexture> textures_loaded;
    void Draw(GLuint shadeID);
    vector<Vertex> get_Vertices( );
    void getFaces( );
    void Bind(GLint posLoc, GLint texcoordLoc, GLint normalLoc);
    void loadMtlFile();
    char* LoadFileContent(string filename);
    vector<Mtl> m_mtls;

    unsigned int mVBO, mEBO;
    unsigned int mIndexCount;
};


#endif //OPENGL_START_08_MODEL_H
