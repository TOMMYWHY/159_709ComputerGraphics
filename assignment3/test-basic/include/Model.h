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

struct NodeTexture {
    unsigned int id;
    string type;
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    string map_Kd_path;
    string map_Ks_path;
    string bump_path;

};

struct Node{
    string name;
    int lineStarIndex;
    int lineEndIndex;
    int face_lineStartIndex;
    int face_lineEndIndex;
    string usemtl;
    string mtl_info;

    vector<glm::vec4>buffer;
    vector<glm::ivec3>indexes;
//    vector<NodeTexture> textures;
   NodeTexture node_texture;

};


using namespace std;
class Model {
public:
    unsigned int VAO;

    GLuint ShadeID;
    string Directory;
    string Model_name;
    string Mtl_file_name;
    vector<Mesh> meshes;
    vector<MeshTexture> textures_loaded;
    vector<NodeTexture> node_texutre;
    vector<Node> nodes;
    vector<vector<string>> file_obj;
    vector<vector<string>> file_mtl;
//    vector<string> mtl_groups;


    Model(string directory,string model_name,GLuint shadeID);
    ~Model();
    void read_obj();
    void read_mtl();

    void get_nodes();
    void get_mtl_info(Node node);

    void loadModel();
    void processNode();
    void setupMesh(Node node);
    void Draw();

    char*  LoadFileContent(string filename);
    void  split(const string &str,vector<string> &v,string spacer);
    string& trim(std::string &s);
};


#endif //OPENGL_START_08_MODEL_H
