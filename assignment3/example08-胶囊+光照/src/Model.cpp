//
// Created by Tommy on 2020/5/22.
//

#include "Model.h"
#include <stb_image.h>
#include <image.h>

Model::Model(string directory,string model_name) {
    this->Directory = directory;
    this->Model_name = model_name;
    vector<Vertex>  vertices = this->get_Vertices();
    this-> getFaces();

    //创建VBO
    glGenBuffers(1,&mVBO);//创建一个buffer
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);//指定BUFFER类型
    //将顶点数据上传至GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(),&vertices[0], GL_STATIC_DRAW);


    mIndexCount = (int)Faces[0].indices.size();
    unsigned int *indexes = new unsigned int[mIndexCount];
    for (int  i = 0; i < mIndexCount; ++i)
    {
        indexes[i] = Faces[0].indices[i];
    }
    glGenBuffers(1,&mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*mIndexCount,indexes,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    this->loadMtlFile();
    cout << "m_mtls"<<m_mtls.size()<<endl;

}

Model::~Model() {}

vector<Vertex> Model::get_Vertices( ) {
    cout <<"model_name" <<this->Model_name<< endl;
  /*  char* fileContent = LoadFileContent(this->Directory+this->Model_name);
//    cout <<"fileContent : " <<fileContent<< endl;
    std::stringstream ssFileContent(fileContent);
    char szOneLine[256];
    std::string temp;
    while (!ssFileContent.eof()){
        memset(szOneLine,0,256);
        ssFileContent.getline(szOneLine,256);
    }*/
    vector<Vertex> tempVertices;
//    vector<unsigned  int> tempIndices;
//    vector<MeshTexture> tempTextures;
    ifstream f;
    f.open(this->Directory+this->Model_name, ios::in);

    if (!f){cout << "Error: Mtl File cannot be opened!"; exit(-2);}
    char buffer[300], word[300];
    unsigned int lineNum = 0;

    while(f.getline(buffer,300)){
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);

        while (!istr.eof())
        {
            istr >> sTmp; //get a word
            ls.push_back(sTmp);

//            cout <<"sTmp : " << sTmp<< endl;
        }
        Vertex tempVertex;
        lineNum++;
        if(ls[0]=="v"){

            tempVertex.Position.x = stringToNum<double>(ls[1]); //long double
            tempVertex.Position.y = stringToNum<double>(ls[2]);
            tempVertex.Position.z = stringToNum<double>(ls[3]);
//            cout <<"tempVertex Position: " <<tempVertex.Position.x << " , "<<tempVertex.Position.y<<" , "<<tempVertex.Position.z<< endl;
        }
        if(ls[0]=="vt"){
            Vertex tempVertex;
            tempVertex.TexCoords.x = stringToNum<double>(ls[1]); //long double
            tempVertex.TexCoords.y = stringToNum<double>(ls[2]);
//            cout <<"tempVertex TexCoords: " <<tempVertex.Position.x << " , "<<tempVertex.Position.y<< endl;
        }
        if(ls[0]=="vn"){
            Vertex tempVertex;
            tempVertex.TexCoords.x = stringToNum<double>(ls[1]); //long double
            tempVertex.TexCoords.y = stringToNum<double>(ls[2]);
            tempVertex.Position.z = stringToNum<double>(ls[3]);

//            cout <<"tempVertex normal: " <<tempVertex.Position.x << " , "<<tempVertex.Position.y<< endl;
        }
        tempVertices.push_back(tempVertex);

        if (ls[0] == "usemtl") {
            Face face;
            cout << ls[1] << endl;
            face.usemtl =ls[1];
            face.lineIndex = lineNum;
//            cout <<" face.lineIndex:"<<  face.lineIndex<<endl;
            Faces.push_back(face);
        }


//        Mesh(tempVertices,tempIndices,tempTextures);
        return tempVertices;
    }






}

void Model::getFaces() {
    struct VertexDefine
    {
        int positionIndex;
        int texcoordIndex;
        int normalIndex;
    };
    std::vector<VertexDefine> vertices;


    ifstream f;
    f.open(this->Directory+this->Model_name, ios::in);

    if (!f){cout << "Error: Mtl File cannot be opened!"; exit(-2);}
    char buffer[300], word[300];
    unsigned int lineNum = 0;
    while(f.getline(buffer,300)){
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);

        while (!istr.eof())
        {
            istr >> sTmp; //get a word
            ls.push_back(sTmp);
        }
//        Vertex tempVertex;
        lineNum++;

//        cout << Faces.size() <<endl;
        if (ls[0] == "f" && lineNum > Faces[0].lineIndex) {
//            cout << ls.size() <<endl;
            for (int i = 1; i < ls.size(); i++) {

                size_t pos = ls[i].find_first_of('/');
                std::string positionIndexStr = ls[i].substr(0, pos);
                size_t pos2 = ls[i].find_first_of('/', pos + 1);
                std::string texcoordIndexStr = ls[i].substr(pos + 1, pos2 - pos - 1);
                std::string normalIndexStr = ls[i].substr(pos2 + 1, ls[i].length() - pos2 - 1);
//            cout <<"positionIndexStr"<< positionIndexStr <<endl;
                VertexDefine vd;
                vd.positionIndex = atoi(positionIndexStr.c_str()) - 1;
                vd.texcoordIndex = atoi(texcoordIndexStr.c_str()) - 1;
                vd.normalIndex = atoi(normalIndexStr.c_str()) - 1;
                int nCurrentVertexIndex = -1;
                size_t nCurrentVerticeCount = vertices.size();
                for (int j = 0; j<nCurrentVerticeCount; ++j)
                {
                    if (vertices[j].positionIndex == vd.positionIndex&&
                        vertices[j].texcoordIndex == vd.texcoordIndex&&
                        vertices[j].normalIndex == vd.normalIndex)
                    {
                        nCurrentVertexIndex = j;
                        break;
                    }
                }
                if (nCurrentVertexIndex == -1)
                {
                    nCurrentVertexIndex = (int)vertices.size();
                    vertices.push_back(vd);
                }
                Faces[0].indices.push_back(nCurrentVertexIndex);

            }
        }
/*

        if (ls[0] == "f" && lineNum < Faces[0].lineIndex && lineNum< Faces[1].lineIndex) {
//            cout <<"Faces[i].lineIndex => "<<Faces[0].lineIndex <<"  ls[1]:"<<  ls[1]<<endl;
        }
        if (ls[0] == "f" && lineNum < Faces[1].lineIndex && lineNum< Faces[2].lineIndex) {
//            cout <<"Faces[i].lineIndex => "<<Faces[0].lineIndex <<"  ls[1]:"<<  ls[1]<<endl;
        }
        if (ls[0] == "f" && lineNum < Faces[2].lineIndex && lineNum< Faces[3].lineIndex) {
//            cout <<"Faces[i].lineIndex => "<<Faces[0].lineIndex <<"  ls[1]:"<<  ls[1]<<endl;
        }
*/




//        Mesh(tempVertices,tempIndices,tempTextures);
    }
}

void Model::Bind(GLint posLoc, GLint texcoordLoc, GLint normalLoc)
{
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glEnableVertexAttribArray(posLoc);//启用顶点属性

    glVertexAttribPointer(posLoc,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0);

    glEnableVertexAttribArray(texcoordLoc);//启用纹理属性
    glVertexAttribPointer(texcoordLoc,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),
                          (void*)(sizeof(float)*3));//指定纹理坐标的起始地址

    glEnableVertexAttribArray(normalLoc);//启用法线属性
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(sizeof(float) * 5));//指定法线坐标的起始地址
    glBindBuffer(GL_ARRAY_BUFFER,0);


    this->loadMtlFile();
//    cout << "mtls::"<<m_mtls[0]->Ka[0]<<endl;

}

/*void Model::loadMtlFile()
{


    ifstream f;
    f.open(this->Directory+"/muro.mtl", ios::in);
    if (!f)
    {
        cout << "Error: Mtl File cannot be opened!";
        exit(-2);
    }

    int index = -1; // 当前材质的下标

    char buffer[300], word[300];
    unsigned int lineNum = 0;
    unsigned int mtl_part = 0;

    while (f.getline(buffer, 300)) {
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);
        while (!istr.eof())
        {
            istr >> sTmp; //get a word
            ls.push_back(sTmp);
        }
        lineNum++;

//        cout <<"mtl:"<<ls[0] <<endl;
        if (ls[0] == "newmtl" ) {
            mtl_part++;
        }
        if(mtl_part ==1 )


        if (ls[0] == "Ka")
        {
            m_mtls[index].Ka[0] = stringToNum<double>(ls[1]);
            m_mtls[index].Ka[1] = stringToNum<double>(ls[2]);
            m_mtls[index].Ka[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "Kd")
        {
            m_mtls[index].Kd[0] = stringToNum<double>(ls[1]);
            m_mtls[index].Kd[1] = stringToNum<double>(ls[2]);
            m_mtls[index].Kd[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "Ks")
        {
            m_mtls[index].Ks[0] = stringToNum<double>(ls[1]);
            m_mtls[index].Ks[1] = stringToNum<double>(ls[2]);
            m_mtls[index].Ks[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "map_Kd")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  "map_Kd imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (this->Directory+"/"+imgPath).c_str();
            m_mtls[index].texture = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        if (ls[0] == "bump")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  " bump imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (this->Directory+"/"+imgPath).c_str();
            m_mtls[index].texture_bump = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        if (ls[0] == "map_Ks")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  "map_Ks imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (this->Directory+"/"+imgPath).c_str();
            m_mtls[index].texture_ks = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        ls.clear();

    }
}*/
/*void Model::loadMtlFile(){
//    char* fileContent = LoadFileContent(this->Directory+"/muro.mtl");
//    cout << "mtl:" <<fileContent<<endl;
//    fileContent.split
    ifstream f;
    f.open(this->Directory+"/muro.mtl", ios::in);
    vector<vector<string>> lines;
    char buffer[300], word[300];
    while (f.getline(buffer, 300)) {
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);
        while (!istr.eof())
        {
            istr >> sTmp; //get a word
            ls.push_back(sTmp);
        }
        lines.push_back(ls);
    }

    Mtl mtl;
    int part = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if(lines[i][j]=="newmtl"){
                cout << lines[i][j+1] <<endl;
                mtl.mtlName = lines[i][j+1];
            }

            part++;
        }
    }


    


}*/
void Model::loadMtlFile()
{
//    cout <<"filename" <<filename+"/capsule.mtl"<< endl;
//    cout <<"filename" <<filename+"/muro.mtl"<< endl;
    ifstream f;
    f.open(this->Directory+"/muro.mtl", ios::in);
//    f.open(filename+"/capsule.mtl", ios::in);

    if (!f)
    {
        cout << "Error: Mtl File cannot be opened!";
        exit(-2);
    }

    int index = -1; // 当前材质的下标

    char buffer[300], word[300];

    while (f.getline(buffer, 300)) {
        vector<string> ls;
        string str(buffer);
        string sTmp;
        istringstream istr(str);
        while (!istr.eof())
        {
            istr >> sTmp; //get a word
            ls.push_back(sTmp);
        }
//        cout <<"mtl:"<<ls[0] <<endl;
        if (ls[0] == "newmtl") {
            Mtl tMtl ;

            tMtl.mtlName = ls[1];
            this->m_mtls.push_back(tMtl);  // 获得一个新的材质
//            cout << m_mtls.size() << endl;
            index = m_mtls.size() - 1;
        }


        if (ls[0] == "Ka")
        {
            m_mtls[index].Ka[0] = stringToNum<double>(ls[1]);
            m_mtls[index].Ka[1] = stringToNum<double>(ls[2]);
            m_mtls[index].Ka[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "Kd")
        {
            m_mtls[index].Kd[0] = stringToNum<double>(ls[1]);
            m_mtls[index].Kd[1] = stringToNum<double>(ls[2]);
            m_mtls[index].Kd[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "Ks")
        {
            m_mtls[index].Ks[0] = stringToNum<double>(ls[1]);
            m_mtls[index].Ks[1] = stringToNum<double>(ls[2]);
            m_mtls[index].Ks[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "map_Kd")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  "map_Kd imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (this->Directory+"/"+imgPath).c_str();
            m_mtls[index].texture = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        if (ls[0] == "bump")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  " bump imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (this->Directory+"/"+imgPath).c_str();
            m_mtls[index].texture_bump = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        if (ls[0] == "map_Ks")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  "map_Ks imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (this->Directory+"/"+imgPath).c_str();
            m_mtls[index].texture_ks = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        ls.clear();

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


void Model::Draw(GLuint shadeID)
{






    for (int i = 0; i < m_mtls.size(); i++) {
        if(m_mtls[i].texture){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,m_mtls[i].texture);
            glUniform1i(glGetUniformLocation(shadeID,"material_diffuse"), 0 );
        }else if(m_mtls[i].texture_bump){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,m_mtls[i].texture);
            glUniform1i(glGetUniformLocation(shadeID,"material_specular"), 1);
        }else if(m_mtls[i].texture_ks){
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D,m_mtls[i].texture);
            glUniform1i(glGetUniformLocation(shadeID,"material_Normal"), 1);
        }


//        glUniform4f(glGetUniformLocation(shadeID,"Ka"),m_mtls[i].Ka[0],m_mtls[i].Ka[1],m_mtls[i].Ka[2],0.0f );
//        glUniform4f(glGetUniformLocation(shadeID,"Kd"),m_mtls[i].Kd[0],m_mtls[i].Ka[1],m_mtls[i].Kd[2],0.0f );
//        glUniform4f(glGetUniformLocation(shadeID,"Ks"),m_mtls[i].Ks[0],m_mtls[i].Ka[1],m_mtls[i].Ks[2],0.0f );

    }


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glDrawElements(GL_TRIANGLES,mIndexCount,GL_UNSIGNED_INT,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}