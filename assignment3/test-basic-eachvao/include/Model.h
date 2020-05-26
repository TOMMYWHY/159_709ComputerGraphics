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

struct VertexBuffer {
    glm::vec4 Position;
    glm::vec4 Normal;
    glm::vec4 TexCoords;
};

/*struct Texture_info{
    unsigned int id;
    string type;
    string path;
};*/

struct NodeTexture {
    unsigned int id;
    string type;
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
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
    int v_count;
    int f_count;
    int v_lineStartIndex;
    int v_lineEndIndex;
    int f_lineStartIndex;
    int f_lineEndIndex;
    string usemtl;

    string mtl_info; //
     int face_amount;
    vector<glm::vec4>buffer;
    vector<glm::ivec3>indexes;
    vector<VertexBuffer> vertices;
//    vector<NodeTexture> textures;
   NodeTexture node_texture;
//   vector<NodeVertex> node_index_vec;

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
//    vector<Mesh> meshes;
//    vector<MeshTexture> textures_loaded;
//    vector<NodeTexture> node_texutre;
    vector<Node> nodes; //
    vector<vector<string>> file_obj; //all words of obj file
    vector<vector<string>> file_mtl; //all words of obj file
//    vector<glm::vec4>total_buffer;
//    vector<glm::ivec3>total_indexes;
    V_Vt_Vns v_t_vn;



    Model(string directory,string model_name,GLuint shadeID);
    ~Model();
    void read_obj();
//    void read_mtl();
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
