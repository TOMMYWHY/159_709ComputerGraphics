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

    struct VertexDefine
    {
        int positionIndex;
        int texcoordIndex;
        int normalIndex;
    };

    struct Face
    {
        int positionIndex;
        int texcoordIndex;
        int normalIndex;
    };

    ifstream f;
    f.open(this->Directory+this->Model_name, ios::in);
    if (!f){cout << "Error: Mtl File cannot be opened!"; exit(-2);}
    char buffer[300], word[300];
    unsigned int lineNum = 0;
    vector<vector<string>> file_vec;
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
        file_vec.push_back(ls);
    }

    cout<< "file_vec:" <<file_vec.size()  << endl;
    vector<Node> nodes;
    int node_star = 0;
    for (int i = 0; i < file_vec.size(); i++) {
        for (int j = 0; j < file_vec[i].size(); j++) {
            if( file_vec[i][j]=="usemtl"){
//                cout<< "usemtl :" <<file_vec[i][j] << " : " << file_vec[i][j+1] << i << endl;
                Node node;
                node.name = file_vec[i-1][1] + file_vec[i-1][2];
                node.lineStarIndex = node_star;
                node.lineEndIndex = i;
                node.usemtl = file_vec[i][j+1];
                nodes.push_back(node);
                node_star = i+1;
            }
        }
    }
    /*find face index*/
    for (int k = 0;k < nodes.size(); k++) {
        if(k  == nodes.size()-1 ){
//            cout << ">>>>>>"<< endl;
            nodes[k].face_lineStartIndex = nodes[k].lineEndIndex;
            nodes[k].face_lineEndIndex = file_vec.size();
          /*  for (int i = nodes[k].lineEndIndex; i < file_vec.size() ; i++) {
//                cout <<file_vec[i][0] <<" "<<file_vec[i][1] <<" " <<file_vec[i][2]  <<" "  <<endl;
            }*/
        }else{
            nodes[k].face_lineStartIndex = nodes[k].lineEndIndex;
            nodes[k].face_lineEndIndex = nodes[k+1].lineEndIndex;
            /*for (int i = nodes[k].lineEndIndex; i < nodes[k+1].lineStarIndex; i++) {
                if(file_vec[i][0]=="f"){
                    cout <<file_vec[i][0] <<" "<<file_vec[i][1] <<" " <<file_vec[i][2] <<" " <<file_vec[i][3] <<" "  <<endl;
                }
            }*/
        }
        cout << "node"<<k<<" : "
                << "name "<< nodes[k].name<<" , "
                << "lineStarIndex "<< nodes[k].lineStarIndex<<" , "
                << "lineEndIndex "<< nodes[k].lineEndIndex<<" , "
                << "face_lineEndIndex "<< nodes[k].face_lineEndIndex<<" , "
                << "usemtl "<< nodes[k].usemtl<<" ; "
        <<endl;
    }





    for (int i = 0; i < nodes.size(); i++) {
        cout<< "nodes:" <<nodes[i].lineEndIndex << endl;
    }
//    for (int k = 0; k < 1; k++) {
    for (int k = 0; k < nodes.size(); k++) {
        vector<glm::vec4>buffer;
        vector<glm::ivec3>indexes;
        vector<Vertex> vertices;
        std::vector<VertexDefine> verticesIndex;

        for (int i = nodes[k].lineStarIndex; i < nodes[k].lineEndIndex; i++) {
            Vertex tempVertex;
            if(file_vec[i][0]=="v"){
                tempVertex.Position.x = stringToNum<double>(file_vec[i][1]); //long double
                tempVertex.Position.y = stringToNum<double>(file_vec[i][2]);
                tempVertex.Position.z = stringToNum<double>(file_vec[i][3]);
            }
            if(file_vec[i][0]=="vt"){
                tempVertex.TexCoords.x = stringToNum<double>(file_vec[i][1]);
                tempVertex.TexCoords.y = stringToNum<double>(file_vec[i][2]);
            }
            if(file_vec[i][0]=="vn"){
                tempVertex.Normal.x = stringToNum<double>(file_vec[i][1]);
                tempVertex.Normal.y = stringToNum<double>(file_vec[i][2]);
                tempVertex.Normal.z = stringToNum<double>(file_vec[i][3]);
            }
            vertices.push_back(tempVertex);
        }

        for (int i = 0; i < vertices.size(); i++) {
//                    cout <<vertices[i].Position.x<<endl;
        }
        /*face*/
        vector<unsigned int> indices;
        vector<Face> faces;
        cout<< "nodes[k].face_lineStartIndex:"<< nodes[k].face_lineStartIndex << endl;
        cout<< "nodes[k].face_lineEndIndex:"<< nodes[k].face_lineEndIndex << endl;

        int sum_f = 0;
        for (int i = nodes[k].face_lineStartIndex; i < nodes[k].face_lineEndIndex; i++) {
//            for (int i = nodes[k].face_lineStartIndex; i < nodes[k].face_lineStartIndex+10; i++) {

            if(file_vec[i][0]=="f"){
//                            cout << file_vec[i][0]<< " " <<file_vec[i][1] << " " << file_vec[i][2]<<endl;
//                cout << file_vec[i].size()<<endl;

                if(file_vec[i].size()-1 == 3){
                    glm::ivec3 each_f_index = glm::ivec3(sum_f,sum_f+1,sum_f+2);
//                        cout<< each_f_index.x <<","<< each_f_index.y<<"," <<each_f_index.z  << endl;
                    indexes.push_back(each_f_index);
                }
                sum_f =sum_f + file_vec[i].size()-1;


                for (int j = 1; j < file_vec[i].size(); j++) {
                    string vertexStr = file_vec[i][j];
//                    cout <<"vertexStr:"<<vertexStr << endl;
                    size_t pos = vertexStr.find_first_of('/');
                    std::string positionIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1);
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
//                    cout<< " f : "<<positionIndexStr << "/" <<texcoordIndexStr <<"/"<<normalIndexStr <<endl;
//                    cout<< atoi(positionIndexStr.c_str()) - 1 <<endl;

                    VertexDefine vd;
                    Face face;
                    face.positionIndex = atoi(positionIndexStr.c_str()) - 1;
                    face.texcoordIndex = atoi(texcoordIndexStr.c_str()) - 1;
                    face.normalIndex = atoi(normalIndexStr.c_str()) - 1;
                    //todo face 的读取
                    faces.push_back(face);
//                    cout<<"face:" <<face.positionIndex <<endl;
                    glm::vec4 bf_position =glm::vec4(vertices[face.positionIndex].Position.x,  vertices[face.positionIndex].Position.y, vertices[face.positionIndex].Position.z,  1.0f);
                    glm::vec4 bf_normal =glm::vec4(vertices[face.normalIndex].Normal.x,  vertices[face.normalIndex].Normal.y, vertices[face.normalIndex].Normal.z,  0.0f);
                    glm::vec4 bf_texcoord =glm::vec4(vertices[face.texcoordIndex].TexCoords.x,  vertices[face.texcoordIndex].TexCoords.y, 0,  0.0f);
                    buffer.push_back(bf_position);
                    buffer.push_back(bf_normal);
                    buffer.push_back(bf_texcoord);
/*                    vd.positionIndex = atoi(positionIndexStr.c_str()) - 1;
                    vd.texcoordIndex = atoi(texcoordIndexStr.c_str()) - 1;
                    vd.normalIndex = atoi(normalIndexStr.c_str()) - 1;

//                    int nCurrentVertexIndex = -1;
                    int nCurrentVertexIndex = 0;
                    size_t nCurrentVerticeCount = verticesIndex.size();
//                    cout << "verticesIndex.size()"<< verticesIndex.size() << endl;
                    for (int j = 0; j<nCurrentVerticeCount; ++j)
                    {
                        if (verticesIndex[j].positionIndex == vd.positionIndex&&
                            verticesIndex[j].texcoordIndex == vd.texcoordIndex&&
                            verticesIndex[j].normalIndex == vd.normalIndex)
                        {
                            nCurrentVertexIndex = j;
                            break;
                        }
                    }
                    if (nCurrentVertexIndex == 0)
                    {
                        nCurrentVertexIndex = (int)verticesIndex.size();
                        verticesIndex.push_back(vd);
                    }
//                    indices.push_back(nCurrentVertexIndex);
//                    cout <<"indices:"<<nCurrentVertexIndex << endl;*/
                }
//                cout << endl;
            }
        }

        for (int i = 0; i < indexes.size(); i++) {
//            cout<< indexes[i].x <<","<< indexes[i].y<<"," <<indexes[i].z  << endl;
        }
        for (int i = 0; i < buffer.size(); i++) {
//            cout<< buffer[i].x <<","<< buffer[i].y<<"," <<buffer[i].z  << endl;
        }
        Part pa;
        pa.buffer = buffer;
        pa.indexes = indexes;
        this->parts.push_back(pa);

//        Mesh(buffer, indexes);
    }
    this->setupMesh(parts[0]);//
}

void Model::setupMesh(Part pa) {
//    Part p1 = parts[0];
    std::vector<glm::vec4> buffer = pa.buffer;
    std::vector<glm::ivec3> indexes = pa.indexes;
//    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Bind VAO, VBO & EBO
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);
    GLuint posLoc = glGetAttribLocation(this->ShadeID, "vert_Position");
    GLuint norLoc = glGetAttribLocation(this->ShadeID, "vert_Normal");
    GLuint texLoc = glGetAttribLocation(this->ShadeID, "vert_UV");
//    GLuint tanLoc = glGetAttribLocation(program, "vert_Tangent");
    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), NULL);
    glVertexAttribPointer(norLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
    glVertexAttribPointer(texLoc, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));
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
    glDrawElements(GL_TRIANGLES, parts[0].indexes.size()*3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
