//
// Created by Tommy on 2020/5/23.
//

#include "Model.h"
Model::~Model() {

}
Model::Model(string directory,string model_name,GLuint shadeID) {
    this->Directory = directory;
    this->Model_name = model_name;
    this->ShadeID =shadeID;
    this->loadModel();
}

void Model::loadModel(){

    this->read_obj();
    this->get_nodes();
    this->read_mtl();
    for (int i = 0; i <this->nodes.size(); i++) {
        this->get_mtl_info(nodes[i]);
    }
    this->processNode();

    for (int i = 0; i <this->nodes.size(); i++) {
        this->setupMesh(nodes[i]);//
    }
}


void Model::setupMesh(Node node) {
    std::vector<glm::vec4> buffer = node.buffer;
    std::vector<glm::ivec3> indexes = node.indexes;
    GLuint vbo = 0;
    GLuint ebo = 0;
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Bind VAO, VBO & EBO
    glBindVertexArray(this->VAO);
//    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);
    GLuint posLoc = glGetAttribLocation(this->ShadeID, "vert_Position");
    GLuint norLoc = glGetAttribLocation(this->ShadeID, "vert_Normal");
    GLuint texLoc = glGetAttribLocation(this->ShadeID, "vert_UV");
//    GLuint tanLoc = glGetAttribLocation(program, "vert_Tangent");
    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));
//    glVertexAttribPointer(tanLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(12*sizeof(float)));
    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(norLoc);
    glEnableVertexAttribArray(texLoc);
//    glEnableVertexAttribArray(tanLoc);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Model::Draw() {
    glBindVertexArray(this->VAO);
    		glDrawElements(GL_TRIANGLES, this->nodes[0].indexes.size() * 3, GL_UNSIGNED_INT, NULL);

//    glBindVertexArray(0);
}

void Model::read_obj() {
    ifstream f;
    f.open(this->Directory+this->Model_name, ios::in);
    if (!f){cout << "Error: Mtl File cannot be opened!"; exit(-2);}
    char buffer[300];
//    unsigned int lineNum = 0;
    while(f.getline(buffer,300)) {
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);
        while (!istr.eof())
        {
            istr >> sTmp; //get a word
            ls.push_back(sTmp);
        }
        this->file_obj.push_back(ls);
        if(ls[0]=="mtllib"){
            this->Mtl_file_name = ls[1];
        }
    }
}

void Model::get_nodes() {
    int node_star = 0;
    for (int i = 0; i < this->file_obj.size(); i++) {
        for (int j = 0; j < this->file_obj[i].size(); j++) {
            if( this->file_obj[i][j]=="usemtl"){
                Node node;
                node.name = this->file_obj[i-1][1] + this->file_obj[i-1][2];
                node.lineStarIndex = node_star;
                node.lineEndIndex = i;
                node.usemtl = file_obj[i][j+1];
                this->nodes.push_back(node);
                node_star = i+1;
            }
        }
    }
    /*find face index*/
    for (int k = 0;k < this->nodes.size(); k++) {
        if(k  == this->nodes.size()-1 ){
//            cout << ">>>>>>"<< endl;
            this->nodes[k].face_lineStartIndex = this->nodes[k].lineEndIndex;
            this->nodes[k].face_lineEndIndex = this->file_obj.size();
        }else{
            this->nodes[k].face_lineStartIndex = this->nodes[k].lineEndIndex;
            this->nodes[k].face_lineEndIndex = this->nodes[k+1].lineEndIndex;
        }
        cout << "node "<<k<<" : "
             << "name "<< nodes[k].name<<" , "
             << "lineStarIndex "<< nodes[k].lineStarIndex<<" , "
             << "lineEndIndex "<< nodes[k].lineEndIndex<<" , "
             << "face_lineEndIndex "<< nodes[k].face_lineEndIndex<<" , "
             << "usemtl "<< nodes[k].usemtl<<" ; "
             <<endl;
    }

}

void Model::processNode() {
    struct Face
    {
        int positionIndex;
        int texcoordIndex;
        int normalIndex;
    };
    for (int k = 0; k < this->nodes.size(); k++) {

        vector<glm::vec4>buffer;
        vector<glm::ivec3>indexes;
        vector<Vertex> vertices;

        for (int i = nodes[k].lineStarIndex; i < nodes[k].lineEndIndex; i++) {
            Vertex tempVertex;
            if(file_obj[i][0]=="v"){
                tempVertex.Position.x = stringToNum<double>(file_obj[i][1]); //long double
                tempVertex.Position.y = stringToNum<double>(file_obj[i][2]);
                tempVertex.Position.z = stringToNum<double>(file_obj[i][3]);
            }
            if(file_obj[i][0]=="vt"){
                tempVertex.TexCoords.x = stringToNum<double>(file_obj[i][1]);
                tempVertex.TexCoords.y = stringToNum<double>(file_obj[i][2]);
            }
            if(file_obj[i][0]=="vn"){
                tempVertex.Normal.x = stringToNum<double>(file_obj[i][1]);
                tempVertex.Normal.y = stringToNum<double>(file_obj[i][2]);
                tempVertex.Normal.z = stringToNum<double>(file_obj[i][3]);
            }
            vertices.push_back(tempVertex);
        }
        /*face*/
        vector<unsigned int> indices;
        vector<Face> faces;
        cout<< "nodes[k].face_lineStartIndex:"<< nodes[k].face_lineStartIndex << endl;
        cout<< "nodes[k].face_lineEndIndex:"<< nodes[k].face_lineEndIndex << endl;

        int sum_f = 0;
        for (int i = nodes[k].face_lineStartIndex; i < nodes[k].face_lineEndIndex; i++) {

            if(file_obj[i][0]=="f"){
                if(file_obj[i].size()-1 == 3){
                    glm::ivec3 each_f_index = glm::ivec3(sum_f,sum_f+1,sum_f+2);
                    indexes.push_back(each_f_index);
                }
                sum_f =sum_f + file_obj[i].size()-1;
                for (int j = 1; j < file_obj[i].size(); j++) {
                    string vertexStr = file_obj[i][j];
                    size_t pos = vertexStr.find_first_of('/');
                    std::string positionIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1);
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
                    Face face;
                    face.positionIndex = atoi(positionIndexStr.c_str()) - 1;
                    face.texcoordIndex = atoi(texcoordIndexStr.c_str()) - 1;
                    face.normalIndex = atoi(normalIndexStr.c_str()) - 1;
                    //todo face 的读取
                    faces.push_back(face);
                    glm::vec4 bf_position =glm::vec4(vertices[face.positionIndex].Position.x,  vertices[face.positionIndex].Position.y, vertices[face.positionIndex].Position.z,  1.0f);
                    glm::vec4 bf_normal =glm::vec4(vertices[face.normalIndex].Normal.x,  vertices[face.normalIndex].Normal.y, vertices[face.normalIndex].Normal.z,  0.0f);
                    glm::vec4 bf_texcoord =glm::vec4(vertices[face.texcoordIndex].TexCoords.x,  vertices[face.texcoordIndex].TexCoords.y, 0,  0.0f);
                    buffer.push_back(bf_position);
                    buffer.push_back(bf_normal);
                    buffer.push_back(bf_texcoord);
                }
            }
        }

        nodes[k].buffer = buffer;
        nodes[k].indexes = indexes;


//        Mesh(buffer, indexes);
    }
}

void Model:: read_mtl(){
    ifstream f;
    f.open(this->Directory+this->Mtl_file_name, ios::in);
    if (!f){cout << "Error: Mtl File cannot be opened!"; exit(-2);}
    char buffer[300];
    unsigned int lineNum = 0;
    while(f.getline(buffer,300)) {
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);
        while (!istr.eof())
        {
            istr >> sTmp; //get a word
            ls.push_back(sTmp);
        }
        this->file_mtl.push_back(ls);
    }
    /*for (int i = 0; i < file_mtl.size(); i++) {
        cout <<file_mtl[i][0] <<endl;
    }*/
}

void Model::get_mtl_info(Node node) {
    char* mtl_file = LoadFileContent(this->Directory+this->Mtl_file_name);
//    char* mtl_file = LoadFileContent(this->Directory+"muro.mtl");
    vector<string> mtl_groups;
    split(mtl_file, mtl_groups, "newmtl");
    for (int i = 0; i < mtl_groups.size(); i++) {
        vector<string> mtl_info;
        split(mtl_groups[i], mtl_info, "\n");
        for (int j = 0; j < mtl_info.size(); j++) {
            if(trim(mtl_info[j]) == node.usemtl){
//                cout << "usemtl----"<<mtl_info[j] <<endl;
                node.mtl_info = mtl_groups[i];
            }
        }
    }
    cout << "========"<<endl;
//    cout << node.mtl_info <<endl;

    //todo add to processing node
    string mtlInfo_all = node.mtl_info;
    vector<vector<string>> mtlInfo_all_p;
    vector<string> lines;
    split(mtlInfo_all, lines, "\n");
    for (int i = 0; i < lines.size(); i++) {
        vector<string> values;
        split(lines[i], values, " ");
//        mtlInfo_all_p.push_back(values);
//        cout << values[0] <<endl;
        for (int j = 0; j < values.size(); j++) {
            if(trim(values[j]) == "Ka"){
                node.node_texture.Ka[0] = stringToNum<double>( trim(values[j+1]) );
                node.node_texture.Ka[1] = stringToNum<double>( trim(values[j+2]) );
                node.node_texture.Ka[2] = stringToNum<double>( trim(values[j+3]) );
//                cout <<"ka:" <<  node.node_texture.Ka[0] <<" " <<   node.node_texture.Ka[1] << " "<< node.node_texture.Ka[2]<<endl;
            }
            if(trim(values[j]) == "Kd"){
                node.node_texture.Kd[0] = stringToNum<double>( trim(values[j+1]) );
                node.node_texture.Kd[1] = stringToNum<double>( trim(values[j+2]) );
                node.node_texture.Kd[2] = stringToNum<double>( trim(values[j+3]) );
            }
             if(trim(values[j]) == "Ks"){
                node.node_texture.Ks[0] = stringToNum<double>( trim(values[j+1]) );
                node.node_texture.Ks[1] = stringToNum<double>( trim(values[j+2]) );
                node.node_texture.Ks[2] = stringToNum<double>( trim(values[j+3]) );
            }
            if(trim(values[j]) == "map_Kd"){
                node.node_texture.map_Kd_path = trim(values[j+1]);
            }
            if(trim(values[j]) == "map_Ks"){
                node.node_texture.map_Ks_path = trim(values[j+1]);
            }
            if(trim(values[j]) == "bump"){
                node.node_texture.bump_path = trim(values[j+1]);
            }
        }

    }

};


char* Model:: LoadFileContent(string filename) {
// Open File
    std::ifstream input(filename);

// Check file is open
    if(!input.good()) {
// Print Error
        std::cerr << "Error: Could not open " << filename << std::endl;

// Return Error
        return 0;
    }

// Find end of file
    input.seekg(0, std::ios::end);

// Calculate Size
    size_t size = input.tellg();

// Allocate required memory
    char *data = new char[size+1];

// Rewind to beginning
    input.seekg(0, std::ios::beg);

// Read file into memory
    input.read(data, size);

// Append '\0'
    data[size] = '\0';

// Close file
    input.close();

// Return file contents
    return data;
}

void Model:: split(const string &str,vector<string> &v,string spacer)
{
    int pos1,pos2;
    int len=spacer.length();     //记录分隔符的长度
    pos1=0;
    pos2=str.find(spacer);
    while( pos2 != string::npos )
    {
        v.push_back( str.substr(pos1,pos2-pos1) );
        pos1 = pos2 + len;
        pos2 = str.find(spacer,pos1);    // 从str的pos1位置开始搜寻spacer
    }
    if(pos1 != str.length()) //分割最后一个部分
        v.push_back(str.substr(pos1));
}

string &Model::trim(std::string &s) {
    if (s.empty())
    {
        return s;
    }

    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;

}
