//
// Created by Tommy on 2020/5/23.
//

#ifndef OPENGL_START_08_MODEL_H
#define OPENGL_START_08_MODEL_H
#include <iostream>
#include <string>
#include <vector>
#include "Mesh.h"
#include "image.h"
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}


struct NodeVertex {
    vector<glm::vec4> PositionsIndex;
    vector<glm::vec4>  NormalsIndex;
    vector<glm::vec4>  TexCoordsIndex;
    vector<int> type;
    vector<glm::vec4>  Tangent;
    vector<glm::vec4>  Bitangent;
};


struct NodeTexture {
    unsigned int id;
    string type;
    glm::vec4 Ka = glm::vec4(0.0f,0.0f,0.0f,0.f);
    glm::vec4 Kd = glm::vec4(0.0f,0.0f,0.0f,0.f);
    glm::vec4 Ks = glm::vec4(0.0f,0.0f,0.0f,0.f);
//    vector<string> std_path;
//    vector<string> tex_type;
    string map_Kd_path;
    GLuint map_Kd_ID;
    string map_Ks_path;
    GLuint map_Ks_ID;
    string bump_path;
    GLuint bump_ID;


};
struct V_Vt_Vns{
    vector<glm::vec4> all_v;
    vector<glm::vec4> all_vt;
    vector<glm::vec4> all_vn;
};

struct Node{
//    string name;
    int line_count;
//    int v_count;
//    int f_count;
    int v_lineStartIndex;
    int v_lineEndIndex;
    int f_lineStartIndex;
    int f_lineEndIndex;
    string usemtl;

    string mtl_info; //
     int face_amount;
    vector<glm::vec4>buffer;
    vector<glm::ivec3>indexes;
   NodeTexture node_texture;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
};

using namespace std;
class Model {
public:
    unsigned int VAO,VBO,EBO;

    GLuint ShadeID;
    string Directory;
    string Model_name; // .obj filename
    string Mtl_file_name; //.mtl filename
    vector<Node> nodes; //
    vector<vector<string>> file_obj; //all words of obj file
//    vector<vector<string>> file_mtl; //all words of obj file
    V_Vt_Vns v_t_vn;



    Model(string directory,string model_name,GLuint shadeID);
    ~Model();
    void read_obj();
    void get_all_v_f();

    void get_nodes();
    void get_node_index();
    void get_mtl_info(char* mtl_file, Node &node);

    void loadModel();
    void processNode(Node &node);
    void setupNode(Node &node);
    void setupNode();
    void Draw();
    void Draw(Node &node);
    void DeleteBuffer();

    char*  LoadFileContent(string filename);
    void  split(const string &str,vector<string> &v,string spacer);
    string& trim(std::string &s);
};


#endif //OPENGL_START_08_MODEL_H
