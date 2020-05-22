//
// Created by Tommy on 2020/5/21.
//

#ifndef OPENGL_START_08_OBJMODEL_H
#define OPENGL_START_08_OBJMODEL_H

#include <OpenGL/OpenGL.h>
#include <vector>
#include <string>
#include "Mesh.h"


class Material  // 材质下面管理一系列面
{
public:
    string mtlName;

    double Ns; //反射指数
    double Ni; //折射指数
    double d; //渐隐指数

    int illum; //光照模型描述格式

    float Ka[3]; //环境反射
    float Kd[3]; //漫反射
    float Ks[3]; //镜反射
    float Ke[3];

    float Tf[3];//滤光透射率

//    bool hasTexture;
    GLuint texture; // kd
    GLuint texture_bump; // nv
    GLuint texture_ks; //ks

    vector<int> triFaces;  // 三个一组组成面
    vector<int> quadFaces; // 四个一组组成面

    // vertex array object;
    int quadNum;  // 四角面个数
    int triNum;   // 三角面个数

    GLdouble *triVertexs;
    GLdouble *triNormals;
    GLdouble *triTextures;

    GLdouble *quadVertexs;
    GLdouble *quadNormals;
    GLdouble *quadTextures;

//    Material() :hasTexture(false) {}
};


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
//    const char*modelFilePath;
    string directory;

public:
    void Init(string modelFilePath);
    void Bind(GLint posLoc,GLint texcoordLoc,GLint normalLoc);
    void Draw();
    void Draw(GLuint shadeId);

    vector<Texture>loadMaterialTextures(  string typeName);

    char* LoadFileContent(string modelFilePath);


    void loadFromFile(string objfile, string mtlfile);
    void loadMtlFile(string filename);
    vector<Material*> m_mtls;

};



#endif //OPENGL_START_08_OBJMODEL_H
