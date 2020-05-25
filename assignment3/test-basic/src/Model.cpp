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
//    for (int i = 0; i <this->nodes.size(); i++) {
//        this->get_mtl_info(nodes[i]);
//    }
    for (int i = 0; i <this->nodes.size(); i++) {
        this->processNode(nodes[i]);
    }
    cout << "node0 " <<  nodes[0].usemtl<<endl;

//    this->setupNode(this->nodes[0]);

//    this->setupMesh(nodes[0]);//
//    for (int i = 0; i <this->nodes.size(); i++) {
//        cout <<"wocao111333 " <<endl;
//        this->setupMesh(nodes[i]);//
//     }
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
void Model::setupNode(Node node) {
    cout <<"nibamib"<< node.name<<endl;
    for (int i = 0; i < node.buffer.size(); i++) {
        cout<<"indexes" << node.buffer[i].x <<  " "<< node.buffer[i].y<<  " " <<node.buffer[i].z<< endl;
    }
}

void Model::setupMesh(Node node) {
//    std::vector<glm::vec4> buffer = node.buffer;
//    std::vector<glm::ivec3> indexes = node.indexes;

    cout <<"22222222 " <<endl;
    cout << node.indexes[0].x<<endl;
    for (int i = 0; i < node.indexes.size(); i++) {
        cout<<"indexes" << node.indexes[i].x <<  " "<< node.indexes[i].y<<  " " <<node.indexes[i].z<< endl;
    }
//    for (int i = 0; i < indexes.size(); i++) {
//        cout << indexes[i].x << indexes[i].y << indexes[i].z<< endl;
//    }
/*
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

}
void Model::Draw() {
    glBindVertexArray(this->VAO);

    /*int texture_amount = 0;
    if(!nodes[0].node_texture.map_Kd_path.empty()){
        glActiveTexture(GL_TEXTURE0+texture_amount );
        glBindTexture(GL_TEXTURE_2D,nodes[0].node_texture.map_Kd_ID);
        texture_amount ++;
        glUniform1i(glGetUniformLocation(ShadeID, "material_diffuse"), 0); // todo v0 tobe texture_amount
    }else{
        glUniform4f(glGetUniformLocation(ShadeID, "Ka"), nodes[0].node_texture.Ka[0],nodes[0].node_texture.Ka[1],nodes[0].node_texture.Ka[2],0.f);
    }
    if(!nodes[0].node_texture.map_Ks_path.empty()){
        glActiveTexture(GL_TEXTURE0 + texture_amount);
        glBindTexture(GL_TEXTURE_2D,nodes[0].node_texture.map_Ks_ID);
        texture_amount ++;
        glUniform1i(glGetUniformLocation(ShadeID, "material_specular"), 1); // texture
    }else{
        glUniform4f(glGetUniformLocation(ShadeID, "Ks"), nodes[0].node_texture.Ks[0],nodes[0].node_texture.Ks[1],nodes[0].node_texture.Ks[2],0.f);
    }
    if(!nodes[0].node_texture.bump_path.empty()){
        glActiveTexture(GL_TEXTURE0 + texture_amount); //normal
        glBindTexture(GL_TEXTURE_2D,nodes[0].node_texture.bump_ID);
        texture_amount ++;
        glUniform1i(glGetUniformLocation(ShadeID, "material_Normal"), 2 ); // texture

    }*/


    glDrawElements(GL_TRIANGLES, this->nodes[0].indexes.size() * 3, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
}



void Model::get_nodes() {
    int node_star = 0;
    for (int i = 0; i < this->file_obj.size(); i++) {
        for (int j = 0; j < this->file_obj[i].size(); j++) {
            if( this->file_obj[i][j]=="usemtl"){
                Node node;
//                node.name = this->file_obj[i-1][1] + this->file_obj[i-1][2];
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
//             << "name "<< nodes[k].name<<" , "
             << "lineStarIndex "<< nodes[k].lineStarIndex<<" , "
             << "lineEndIndex "<< nodes[k].lineEndIndex<<" , "
             << "face_lineEndIndex "<< nodes[k].face_lineEndIndex<<" , "
             << "usemtl "<< nodes[k].usemtl<<" ; "
             <<endl;
    }

}

void Model::processNode(Node node) {

//    int use_mtl=0;
    vector<glm::vec4> temp_Positions;
    vector<glm::vec4> temp_TexCoords;
    vector<glm::vec4> temp_Normals;
    NodeVertex temp_node_index;
    for (int i = node.lineStarIndex; i < node.face_lineEndIndex; i++){
//        Vertex tempVertex;

        if(file_obj[i][0]=="v"){
            glm::vec3 temp_pos;
            temp_pos.x = stringToNum<double>(file_obj[i][1]); //long double
            temp_pos.y = stringToNum<double>(file_obj[i][2]);
            temp_pos.z = stringToNum<double>(file_obj[i][3]);
            temp_Positions.push_back(glm::vec4(temp_pos,1.0f));
        }
        if(file_obj[i][0]=="vt"){
            glm::vec2 temp_tex;
            temp_tex.x = stringToNum<double>(file_obj[i][1]); //long double
            temp_tex.y = stringToNum<double>(file_obj[i][2]);
            temp_TexCoords.push_back(glm::vec4(temp_tex,0.0f,0.0f));
        }
        if(file_obj[i][0]=="vn"){
            glm::vec3 temp_nor;
            temp_nor.x = stringToNum<double>(file_obj[i][1]); //long double
            temp_nor.y = stringToNum<double>(file_obj[i][2]);
            temp_nor.z = stringToNum<double>(file_obj[i][3]);
            temp_Normals.push_back(glm::vec4(temp_nor,0.0f));
        }
        if(file_obj[i][0]=="usemtl"){
//            use_mtl =1;
        }
        if(file_obj[i][0]=="f"){
            node.face_amount++;
            int vertexIndex[4],UVIndex[4],normalIndex[4];
//            cout <<"file_obj[i].size():"<<file_obj[i].size()<<endl;
                for (int j = 1; j < file_obj[i].size(); j++) {
                    string vertexStr = file_obj[i][j];
                    size_t pos = vertexStr.find_first_of('/');
                    std::string positionIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1);
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
                    vertexIndex[j-1] = atoi(positionIndexStr.c_str()) - 1;
                    UVIndex[j-1] = atoi(texcoordIndexStr.c_str()) - 1;
                    normalIndex[j-1] = atoi(normalIndexStr.c_str()) - 1;

                }
                if(file_obj[i].size()==4){
                    temp_node_index.type.push_back(3);
                    temp_node_index.PositionsIndex.push_back(glm::vec4(vertexIndex[0],vertexIndex[1],vertexIndex[2],0));
                    temp_node_index.TexCoordsIndex.push_back(glm::vec4(UVIndex[0],UVIndex[1],UVIndex[2],0));
                    temp_node_index.NormalsIndex.push_back(glm::vec4(normalIndex[0],normalIndex[1],normalIndex[2],0));
                }
                if(file_obj[i].size()==5){
                    temp_node_index.type.push_back(3);
                    temp_node_index.PositionsIndex.push_back(glm::vec4(vertexIndex[0],vertexIndex[1],vertexIndex[2],vertexIndex[3]));
                    temp_node_index.TexCoordsIndex.push_back(glm::vec4(UVIndex[0],UVIndex[1],UVIndex[2],UVIndex[3]));
                    temp_node_index.NormalsIndex.push_back(glm::vec4(normalIndex[0],normalIndex[1],normalIndex[2],normalIndex[3]));
                }
        }
    }

    int index_count =0;
    cout <<"node.face_amount:" << node.face_amount<<endl;
//    cout <<"temp_node_index.PositionsIndex.size():" << temp_node_index.PositionsIndex.size()<<endl;
    vector<glm::vec4>temp_buffer;
    vector<glm::ivec3>temp_indexes;

    for (int i = 0; i <temp_node_index.PositionsIndex.size(); i++) {

        temp_buffer.push_back(temp_Positions[temp_node_index.PositionsIndex[i].x]);
        temp_buffer.push_back(temp_TexCoords[temp_node_index.TexCoordsIndex[i].x]);
        temp_buffer.push_back(    temp_Normals[temp_node_index.NormalsIndex[i].x]);
        /* point 1 */
        temp_buffer.push_back(temp_Positions[temp_node_index.PositionsIndex[i].y]);
        temp_buffer.push_back(temp_TexCoords[temp_node_index.TexCoordsIndex[i].y]);
        temp_buffer.push_back(    temp_Normals[temp_node_index.NormalsIndex[i].y]);
        /* point 2 */
        temp_buffer.push_back(temp_Positions[temp_node_index.PositionsIndex[i].z]);
        temp_buffer.push_back(temp_TexCoords[temp_node_index.TexCoordsIndex[i].z]);
        temp_buffer.push_back(    temp_Normals[temp_node_index.NormalsIndex[i].z]);
        /*face == 3*/
        if(temp_node_index.type[i] ==3){
            temp_indexes.push_back(glm::ivec3(index_count,index_count+1,index_count+2));
            index_count = index_count+3;
        }

        /*face == 4*/
        else if(temp_node_index.type[i] ==4){
            temp_buffer.push_back(temp_Positions[temp_node_index.PositionsIndex[i].w]);
            temp_buffer.push_back(temp_TexCoords[temp_node_index.TexCoordsIndex[i].w]);
            temp_buffer.push_back(    temp_Normals[temp_node_index.NormalsIndex[i].w]);
            temp_indexes.push_back(glm::ivec3(index_count,index_count+1,index_count+2));
            temp_indexes.push_back(glm::ivec3(index_count,index_count+2,index_count+3));
            index_count = index_count+4;
        }
    }
    node.indexes = temp_indexes;
    node.buffer = temp_buffer;


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

//    cout << "node map kd "<< node.node_texture.map_Kd_path<<endl;
    int x,y,n;
     if(!node.node_texture.map_Kd_path.empty()){
         const char* url =  (this->Directory + node.node_texture.map_Kd_path).c_str();
         node.node_texture.map_Kd_ID = loadTexture2D(url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
     }
    if(!node.node_texture.map_Ks_path.empty()){
        const char* url = (this->Directory +  node.node_texture.map_Ks_path).c_str();
        node.node_texture.map_Ks_ID = loadTexture2D(url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
    }
    if(!node.node_texture.bump_path.empty()){
        const char* url = (this->Directory +  node.node_texture.bump_path).c_str();
        node.node_texture.bump_ID = loadTexture2D(url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
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

