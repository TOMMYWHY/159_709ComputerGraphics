//
// Created by Tommy on 2020/5/21.
//

#ifndef OPENGL_START_08_OBJMODEL_H
#define OPENGL_START_08_OBJMODEL_H

#include <OpenGL/OpenGL.h>
#include <vector>
#include <string>
#include "Mesh.h"

struct VertexData
{
    float position[3];
    float texcoord[2];
    float normal[3];
};

struct Texture{
    unsigned int id;
    string type;
    string path;
};
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class ObjModel {

public:
    vector<Mesh> meshes;//

    unsigned int mVBO, mEBO;
    unsigned int mIndexCount;
public:
    void Init(const char*modelFilePath);
    void Bind(GLint posLoc,GLint texcoordLoc,GLint normalLoc);
    void Draw();
//    void Draw(GLuint shadeId);

    vector<Texture>loadMaterialTextures(  string typeName);

    char* LoadFileContent(const char* modelFilePath);

};



#endif //OPENGL_START_08_OBJMODEL_H
