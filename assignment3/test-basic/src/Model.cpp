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
    this->get_all_v_f();
    this->get_node_index();
    cout <<"Model_name : "<<this->Model_name << ", Mtl_file_name : "<< this->Mtl_file_name  <<endl;
    this->get_nodes();
    cout<<"nodes.size : " << this->nodes.size()<<endl;
//    this->read_mtl();
    char* mtl_file = LoadFileContent(this->Directory+this->Mtl_file_name);

    for (int i = 0; i <this->nodes.size(); i++) {
        this->processNode(nodes[i]);
        this->get_mtl_info(mtl_file, nodes[i]);
    }
    for (int i = 0; i <this->nodes.size(); i++) {
        this->setupNode(nodes[i]);

    }
//    this->setupNode();
}
void Model::read_obj() {
    ifstream f;
    f.open(this->Directory+this->Model_name, ios::in);
    if (!f){cout << "Error: Obj File cannot be opened!"; exit(-2);}
    char buffer[300];
    while(f.getline(buffer,300)) {
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);
        while (!istr.eof())
        {
            istr >> sTmp;
            ls.push_back(sTmp);
        }
        this->file_obj.push_back(ls);
        if(ls[0]=="mtllib"){
            this->Mtl_file_name = ls[1];
        }
    }

}
/*void Model::setupNode() {
    std::vector<glm::vec4> buffer = this->total_buffer;
    std::vector<glm::ivec3> indexes =this->total_indexes;

    for (int i = 0; i < indexes.size(); i++) {
        cout <<indexes[i].x<< "\n" <<indexes[i].y<< "\n" <<indexes[i].z  <<endl;
    }
    for (int i = 0; i < buffer.size(); i++) {
//        cout <<buffer[i].x<< " " <<buffer[i].y<< " " <<buffer[i].z<< " " <<buffer[i].w  <<endl;
    }
//    GLuint vbo = 0;
//    GLuint ebo = 0;
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
    glGenBuffers(1, &(this->EBO));

    // Bind VAO, VBO & EBO
    glBindVertexArray(this->VAO);
//    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
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

}*/

void Model::setupNode(Node &node) {
    std::vector<glm::vec4> buffer = node.buffer;
    std::vector<glm::ivec3> indexes = node.indexes;

    cout << "node: "<<  node.usemtl<<endl;

    glGenVertexArrays(1, &(node.vao));
    glGenBuffers(1, &(node.vbo));
    glGenBuffers(1, &(node.ebo));

    // Bind VAO, VBO & EBO
    glBindVertexArray(node.vao);
//    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, node.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node.ebo);
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

void Model:: get_all_v_f(){
    for (int i = 0; i < file_obj.size(); i++) {
        if(file_obj[i][0]=="v"){
            glm::vec3 temp_pos;
            temp_pos.x = stringToNum<double>(file_obj[i][1]); //long double
            temp_pos.y = stringToNum<double>(file_obj[i][2]);
            temp_pos.z = stringToNum<double>(file_obj[i][3]);
            v_t_vn.all_v.push_back(glm::vec4(temp_pos,1.0f));
//            cout <<"temp_pos : " <<temp_pos.x<< " " <<temp_pos.y<< " " <<temp_pos.z  <<endl;
        }
        if(file_obj[i][0]=="vt"){
            glm::vec2 temp_tex;
            temp_tex.x = stringToNum<double>(file_obj[i][1]); //long double
            temp_tex.y = stringToNum<double>(file_obj[i][2]);
            /*temp_tex.y = stringToNum<double>(file_obj[i][1]); //long double
            temp_tex.x = stringToNum<double>(file_obj[i][2]);*/
            v_t_vn.all_vt.push_back(glm::vec4(temp_tex.x,1-temp_tex.y,0.0f,0.0f));
//            cout <<"temp_tex : " <<temp_tex.x<< " " <<temp_tex.y<< " "  <<endl;
        }

        if(file_obj[i][0]=="vn"){
            glm::vec3 temp_nor;
            temp_nor.x = stringToNum<double>(file_obj[i][1]); //long double
            temp_nor.y = stringToNum<double>(file_obj[i][2]);
            temp_nor.z = stringToNum<double>(file_obj[i][3]);
            v_t_vn.all_vn.push_back(glm::vec4(temp_nor,0.0f));
//                        cout <<"temp_nor : " <<temp_nor.x<< " " <<temp_nor.y<< " " <<temp_nor.z  <<endl;

        }
    }


};

void Model::get_node_index() {

    char* obj_file = LoadFileContent(this->Directory+this->Model_name);
    string str = obj_file;
//        cout << "str:"<<str<<endl;
//    int num = count(str.begin(),str.end(),'g');
//    cout << "num:"<<num<<endl;

    vector<string> node_groups;
    split(obj_file, node_groups, "g default");
//    cout<<node_groups.size() <<endl;
    for (int i = 0; i < node_groups.size(); i++){
        int num = count(node_groups[i].begin(),node_groups[i].end(),'\n');
        cout << "num:"<<num<<endl;

//            cout<<node_groups[i]<<endl;
        vector<string> node_lines;
    split(node_groups[i], node_lines, "\n");
        int v_count = 0;
        int f_count = 0;
        int s_count = 0;
        cout <<"node_lines.size :  => "<<node_lines.size() <<endl;

        for (int j = 0; j < node_lines.size(); j++) {
            if(node_lines[j].c_str()[0] =='v'){
                v_count++;
            }
            if(node_lines[j].c_str()[0] =='f'){
                f_count++;
            }
        }
        if(v_count!=0 && f_count!=0){
//            NodeIndex nodeIndex;
            Node node;
//            node.v_count=v_count;
//            node.f_count=f_count;
            node.line_count=node_lines.size();
            this->nodes.push_back(node);
//            cout << "v_count : "<<v_count<<endl;
//            cout << "f_count : "<<f_count<<endl;
        }
    }
}

void Model::get_nodes() {
    int node_start_index = 3;
    for (int k = 0;k < this->nodes.size(); k++) {
            this->nodes[k].v_lineStartIndex = node_start_index;
            this->nodes[k].f_lineEndIndex =node_start_index + this->nodes[k].line_count;
            node_start_index =  this->nodes[k].f_lineEndIndex;
        cout << "node "<<k<<" : "
             << "line_count :"<< nodes[k].line_count<<" , "
             << "v_lineStartIndex :"<< nodes[k].v_lineStartIndex<<" , "
             << "f_lineEndIndex :"<< nodes[k].f_lineEndIndex<<" , "
             << "usemtl :"<< nodes[k].usemtl<<" ; "
             <<endl;
    }
}

void Model::processNode(Node &node) {
    vector<glm::vec4> temp_Positions;
    vector<glm::vec4> temp_TexCoords;
    vector<glm::vec4> temp_Normals;
    NodeVertex temp_node_index;
    for (int i = node.v_lineStartIndex; i < node.f_lineEndIndex; i++)
    {
        if(file_obj[i][0]=="usemtl"){
            node.usemtl =file_obj[i][1];
//            cout <<"usemtl xxoo : " <<file_obj[i][0]<< " " <<file_obj[i][1]<< " " <<endl;
        }
        if(file_obj[i][0]=="f"){
            node.face_amount++;
            int vertexIndex[4],UVIndex[4],normalIndex[4];
//            cout <<"file_obj[i].size():"<<file_obj[i].size()<<endl;
                for (int j = 1; j < file_obj[i].size(); j++) { // oeut of "f"
                    string vertexStr = file_obj[i][j]; //  AA/BB/CC
                    size_t pos = vertexStr.find_first_of('/');
                    std::string positionIndexStr = vertexStr.substr(0, pos); //AA
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1); //BB
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);//CC
                    vertexIndex[j-1] = atoi(positionIndexStr.c_str()) - 1; // f 中所有的 AA
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
                    temp_node_index.type.push_back(4);
                    temp_node_index.PositionsIndex.push_back(glm::vec4(vertexIndex[0],vertexIndex[1],vertexIndex[2],vertexIndex[3]));
                    temp_node_index.TexCoordsIndex.push_back(glm::vec4(UVIndex[0],UVIndex[1],UVIndex[2],UVIndex[3]));
                    temp_node_index.NormalsIndex.push_back(glm::vec4(normalIndex[0],normalIndex[1],normalIndex[2],normalIndex[3]));
                }
        }
    }
//    cout << "---------------------------------------------------------------------------------------------" << endl;
    /*cout << "node "<<" : "
         << "face_amount :"<< node.face_amount<<" , "
         << "v_lineStartIndex :"<< node.v_lineStartIndex<<" , "
         << "v_lineEndIndex :"<< node.v_lineEndIndex<<" , "
         << "f_lineStartIndex :"<< node.f_lineStartIndex<<" , "
         << "f_lineEndIndex :"<< node.f_lineEndIndex<<" , "
         << "usemtl :"<< node.usemtl<<" ; "
         <<endl;*/
    cout <<"node.face_amount:" << node.face_amount<<endl;
    cout <<"temp_node_index.PositionsIndex.size :" << temp_node_index.PositionsIndex.size()<<endl;
    vector<glm::vec4>temp_buffer;
    vector<glm::ivec3>temp_indexes;
    int index_count =0;
    for (int i = 0; i < temp_node_index.PositionsIndex.size(); i++)
//    for (int i = 0; i < node.face_amount; i++) //todo
    {
        /* point 0 */
        temp_buffer.push_back(this->v_t_vn.all_v[temp_node_index.PositionsIndex[i].x]);
        temp_buffer.push_back(this->v_t_vn.all_vn[temp_node_index.NormalsIndex[i].x]);
        temp_buffer.push_back(this->v_t_vn.all_vt[temp_node_index.TexCoordsIndex[i].x]);
        /* point 1 */
        temp_buffer.push_back(this->v_t_vn.all_v[temp_node_index.PositionsIndex[i].y]);
        temp_buffer.push_back(    this->v_t_vn.all_vn[temp_node_index.NormalsIndex[i].y]);
        temp_buffer.push_back(this->v_t_vn.all_vt[temp_node_index.TexCoordsIndex[i].y]);
        /* point 2 */
        temp_buffer.push_back(this->v_t_vn.all_v[temp_node_index.PositionsIndex[i].z]);
        temp_buffer.push_back(    this->v_t_vn.all_vn[temp_node_index.NormalsIndex[i].z]);
        temp_buffer.push_back(this->v_t_vn.all_vt[temp_node_index.TexCoordsIndex[i].z]);
        /*face == 3*/
        if(temp_node_index.type[i] ==3){
            temp_indexes.push_back(glm::ivec3(index_count,index_count+1,index_count+2));
            index_count = index_count+3;
        }

        /*face == 4*/
        else if(temp_node_index.type[i] ==4){
            temp_buffer.push_back(this->v_t_vn.all_v[temp_node_index.PositionsIndex[i].w]);
            temp_buffer.push_back(    this->v_t_vn.all_vn[temp_node_index.NormalsIndex[i].w]);
            temp_buffer.push_back(this->v_t_vn.all_vt[temp_node_index.TexCoordsIndex[i].w]);
            temp_indexes.push_back(glm::ivec3(index_count,index_count+1,index_count+2));
            temp_indexes.push_back(glm::ivec3(index_count,index_count+2,index_count+3));
            index_count = index_count+4;
        }
    }
    node.indexes = temp_indexes;
    node.buffer = temp_buffer;
}



void Model::get_mtl_info(char* mtl_file, Node &node) {
    vector<string> mtl_groups;
    split(mtl_file, mtl_groups, "newmtl");

    for (int i = 0; i < mtl_groups.size(); i++) {
//        cout <<mtl_groups[i]  << endl;
        vector<string> mtl_info;
        split(mtl_groups[i], mtl_info, "\n");
        for (int j = 0; j < mtl_info.size(); j++) {
//            cout << " ----- "<< mtl_info[j]  << endl;

            if(trim(mtl_info[j]) == node.usemtl){
//                cout << "usemtl----"<<mtl_info[j] <<endl;
                node.mtl_info = mtl_groups[i];
            }
        }
    }
    cout << "========"<<endl;
//    cout << "node.mtl_info : " << node.usemtl <<"----"  <<node.mtl_info <<endl;

    //todo add to processing node

    string mtlInfo_all = node.mtl_info; // 一个 mtl 的所有信息
//            cout << mtlInfo_all <<endl;

    vector<string> lines;
    split(mtlInfo_all, lines, "\n");
    for (int i = 0; i < lines.size(); i++) {
        vector<string> values; //
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
//                cout << "map_Kd : " <<trim(values[j+1]) <<endl;
            }
            if(trim(values[j]) == "map_Ks"){
                node.node_texture.map_Ks_path = trim(values[j+1]);
//                cout << "map_Ks : " <<trim(values[j+1]) <<endl;

            }
            if(trim(values[j]) == "bump"){
                node.node_texture.bump_path = trim(values[j+1]);
//                cout << "bump : " <<trim(values[j+1]) <<endl;
            }
        }

    }
//    cout << "node map kd "<< node.node_texture.map_Kd_path<<endl;
    int x,y,n;
     if(!node.node_texture.map_Kd_path.empty()){
         const char* url =  (this->Directory + node.node_texture.map_Kd_path).c_str();
//         cout << url <<endl;
         node.node_texture.map_Kd_ID = loadTexture2D(url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
     }
    if(!node.node_texture.map_Ks_path.empty()){
        const char* url = (this->Directory +  node.node_texture.map_Ks_path).c_str();
//        cout << url <<endl;
        node.node_texture.map_Ks_ID = loadTexture2D(url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
    }
    if(!node.node_texture.bump_path.empty()){
        const char* url = (this->Directory +  node.node_texture.bump_path).c_str();
//        cout << url <<endl;
        node.node_texture.bump_ID = loadTexture2D(url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);
    }
};


void Model::Draw(Node &node) {
    glBindVertexArray(node.vao);

    int texture_amount = 0;
    if(!node.node_texture.map_Kd_path.empty()){
        glActiveTexture(GL_TEXTURE0+texture_amount );
        glBindTexture(GL_TEXTURE_2D,node.node_texture.map_Kd_ID);
        texture_amount ++;
        glUniform1i(glGetUniformLocation(ShadeID, "material_diffuse"), 0); // todo v0 tobe texture_amount
    }
    if(!node.node_texture.map_Ks_path.empty()){
        glActiveTexture(GL_TEXTURE0 + texture_amount);
        glBindTexture(GL_TEXTURE_2D,node.node_texture.map_Ks_ID);
        texture_amount ++;
        glUniform1i(glGetUniformLocation(ShadeID, "material_specular"), 1); // texture
    }
    if(!node.node_texture.bump_path.empty()){
        glActiveTexture(GL_TEXTURE0 + texture_amount); //normal
        glBindTexture(GL_TEXTURE_2D,node.node_texture.bump_ID);
        texture_amount ++;
        glUniform1i(glGetUniformLocation(ShadeID, "material_Normal"), 2 ); // texture

    }

    glUniform4f(glGetUniformLocation(ShadeID, "uni_Ka"), node.node_texture.Ka[0],node.node_texture.Ka[1],node.node_texture.Ka[2],0.f);
    glUniform4f(glGetUniformLocation(ShadeID, "uni_Kd"), node.node_texture.Kd[0],node.node_texture.Kd[1],node.node_texture.Kd[2],0.f);
    glUniform4f(glGetUniformLocation(ShadeID, "uni_Ks"), node.node_texture.Ks[0],node.node_texture.Ks[1],node.node_texture.Ks[2],0.f);




    glDrawElements(GL_TRIANGLES, node.indexes.size() * 3, GL_UNSIGNED_INT, NULL);


    glBindVertexArray(0);
}


void Model::DeleteBuffer() {
    for (int i = 0; i < nodes.size(); i++) {
        glDeleteVertexArrays(1, &(nodes[i].vao));
        glDeleteBuffers(1, &(nodes[i].vbo));
        glDeleteBuffers(1, &(nodes[i].ebo));
    }

}

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





