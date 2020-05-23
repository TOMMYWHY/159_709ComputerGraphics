//
// Created by Tommy on 2020/5/23.
//

#include "Model.h"
Model::~Model() {

}
Model::Model(string directory,string model_name) {
    this->Directory = directory;
    this->Model_name = model_name;
    this->loadModel();
}



void Model::loadModel(){

    struct VertexDefine
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
    for (int k = 0; k < 1; k++) {
//    for (int k = 0; k < nodes.size(); k++) {
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

        /*face*/
        vector<unsigned int> indices;
        for (int i = nodes[k].face_lineStartIndex; i < nodes[k].face_lineEndIndex; i++) {
            if(file_vec[i][0]=="f"){
            //                cout << file_vec[i][0]<< " " <<file_vec[i][1] << " " << file_vec[i][2]<<endl;
                for (int j = 0; j < file_vec[i].size(); j++) {
//                    cout << file_vec[i][j] << " ";
                    string vertexStr;

                    //todo face 的读取
                    size_t pos = vertexStr.find_first_of('/');
                    std::string positionIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1);
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
                    VertexDefine vd;
                    vd.positionIndex = atoi(positionIndexStr.c_str()) - 1;
                    vd.texcoordIndex = atoi(texcoordIndexStr.c_str()) - 1;
                    vd.normalIndex = atoi(normalIndexStr.c_str()) - 1;
                    int nCurrentVertexIndex = -1;
                    size_t nCurrentVerticeCount = verticesIndex.size();
                    cout << "verticesIndex.size()"<< verticesIndex.size() << endl;
                    /*for (int j = 0; j<nCurrentVerticeCount; ++j)
                    {
                        if (vertices[j].Position == vd.positionIndex&&
                            vertices[j].texcoordIndex == vd.texcoordIndex&&
                            vertices[j].normalIndex == vd.normalIndex)
                        {
                            nCurrentVertexIndex = j;
                            break;
                        }
                    }*/
                }
                cout << endl;
            }
        }


//        Mesh(vertices, indices, textures);
    }
}