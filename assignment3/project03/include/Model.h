//
// Created by Tommy on 2020/5/23.
//

#ifndef OPENGL_START_08_MODEL_H
#define OPENGL_START_08_MODEL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "image.h"
using namespace std;


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
    string type;
    glm::vec4 Ka = glm::vec4(0.0f,0.0f,0.0f,0.f);
    glm::vec4 Kd = glm::vec4(0.0f,0.0f,0.0f,0.f);
    glm::vec4 Ks = glm::vec4(0.0f,0.0f,0.0f,0.f);
    float Ns = 1.0f;
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
    int line_count;
    int v_lineStartIndex;
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
    GLuint ShadeID;
    string Directory;
    string Model_name; // .obj filename
    string Mtl_file_name; //.mtl filename
    vector<Node> nodes; //
    vector<vector<string>> file_obj; //all words of obj file
    V_Vt_Vns v_t_vn;
    int  nodes_num;
    float SCALE ;
    float POS_y ;

    Model(string directory,string model_name,GLuint shadeID,float Scale,float Pos_y);
    ~Model();
    void read_obj();
    void get_all_v_f();
    void get_nodes();
    void get_node_index();
    void get_mtl_info(char* mtl_file, Node &node);
    void loadModel();
    void processNode(Node &node);
    void setupNode(Node &node);
    void Draw(Node &node);
    void DeleteBuffer();
    char*  LoadFileContent(string filename);
    void  split(const string &str,vector<string> &v,string spacer);
    string& trim(std::string &s);
};


#endif //OPENGL_START_08_MODEL_H
