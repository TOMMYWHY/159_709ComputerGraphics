//
// Created by Tommy on 2020/5/20.
//

#include "Model.h"
#include <fstream>
#include <iostream>



Model::Model(string path) {
    this->loadModel(path);
//    this->directory;
}

Model::~Model() {

}




void Model::loadModel(string path) {
    /*xxxxxxxxxx*/
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace); //todo 如果uv翻转过，去掉 aiProcess_FlipUVs
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    /*xxxxxxxxxx*/
//    this->processNode(scene->mRootNode,scene);

    directory = path.substr(0, path.find_last_of('/'));

    cout << "directory : "<< directory<<endl;
    cout << "path : "<< path<<endl;

}

void Model::processNode(aiNode *node, const aiScene *scene) {
    cout << "node name : "<<node->mName.data<< endl;

    for (int i = 0; i < node->mNumMeshes; i++) {
       aiMesh* curMesh  = scene->mMeshes[node->mMeshes[i]];
       this->meshes.push_back(processMesh(curMesh, scene));

    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> tempVertices;
    vector<unsigned  int> tempIndices;
    vector<Texture> tempTextures;

    glm::vec3 tempVec;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex tempVertex;

        tempVertex.Position.x = mesh->mVertices[i].x;
        tempVertex.Position.y = mesh->mVertices[i].y;
        tempVertex.Position.z = mesh->mVertices[i].z;

        tempVertex.Normal.x = mesh->mNormals[i].x;
        tempVertex.Normal.y = mesh->mNormals[i].y;
        tempVertex.Normal.z = mesh->mNormals[i].z;

        if(mesh->mTextureCoords[0] ){
            tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
            tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
        }else{
            tempVertex.TexCoords = glm::vec2(0,0);
        }
        tempVertices.push_back(tempVertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++) {
        for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
        tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }
    return Mesh(tempVertices,tempIndices,{});
}

void Model::Draw(Shade *shade) {
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shade);
    }
}


