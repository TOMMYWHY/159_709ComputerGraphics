//
// Created by Tommy on 2020/5/20.
//

#ifndef OPENGL_DEMO_MODEL_H
#define OPENGL_DEMO_MODEL_H

#define GLFW_INCLUDE_GLCOREARB
//#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shade.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shade.h"
#include <iostream>


using namespace std;

class Model {
public:
    Model(string path);
    ~Model();
    vector<Mesh> meshes;
    string directory;
    void Draw(Shade* shade);

private:
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

};


#endif //OPENGL_DEMO_MODEL_H
