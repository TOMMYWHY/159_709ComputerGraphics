//
// Created by Tommy on 2020/5/21.
//

#include "ObjModel.h"
#include "utils.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stb_image.h>
#include <image.h>

template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

void ObjModel::Init(string modelFilePath)
{
    this->directory = modelFilePath.substr(0, modelFilePath.find_last_of('/'));

    struct VertexInfo
    {
        float v[3];
        VertexInfo()
        {
            memset(v,0,sizeof(float)*3);
        }
    };

    struct VertexDefine
    {
        int positionIndex;
        int texcoordIndex;
        int normalIndex;
    };




    /*

    C++中，iostream类重载了运算符>>和<<
    >>用于cin对象，表示从标准输入，输入数据到变量中
    <<用于cout对象，表示将变量数据，输出到标准输出中
    */

    std::vector<VertexInfo> positions;//顶点坐标
    std::vector<VertexInfo> texcoords;//纹理坐标
    std::vector<VertexInfo> normals;//法线

    std::vector<VertexDefine> vertices;
    std::vector<unsigned int> faces;

    //加载模型文件
    char* fileContent = LoadFileContent(modelFilePath);
    //解析模型文件
    //stringstream是字符串流 ,它将流与存储在内存中的string对象绑定起来
    std::stringstream ssFileContent(fileContent);
    char szOneLine[256];
    std::string temp;
    while (!ssFileContent.eof())
    {
        memset(szOneLine,0,256);
        ssFileContent.getline(szOneLine,256);
        if (strlen(szOneLine)>0)
        {
            std::stringstream ssOneLine(szOneLine);
            if (szOneLine[0]=='v')//解析顶点信息
            {

                if (szOneLine[1] == 't')//解析纹理坐标
                {
                    VertexInfo vi;
                    ssOneLine >> temp;//vt
                    ssOneLine >> vi.v[0];
                    ssOneLine >> vi.v[1];
                    texcoords.push_back(vi);
                }
                else if (szOneLine[1] == 'n')//解析法线坐标
                {
                    VertexInfo vi;
                    ssOneLine >> temp;//vn
                    ssOneLine >> vi.v[0];
                    ssOneLine >> vi.v[1];
                    ssOneLine >> vi.v[2];
                    normals.push_back(vi);
                }
                else //解析顶点信息
                {
                    VertexInfo vi;
                    ssOneLine >> temp;//v
                    ssOneLine >> vi.v[0];
                    ssOneLine >> vi.v[1];
                    ssOneLine >> vi.v[2];
                    positions.push_back(vi);
                }
            }
            else if (szOneLine[0]=='f') //解析面信息
            {

                string x = szOneLine;
                string buf;
                stringstream ss(x);
                vector<string> tokens;
                while (ss >> buf){
                    tokens.push_back(buf);
                }
                for (int i = 0; i < tokens.size(); i++) {
//                    cout << tokens[i]<<endl;
                }
//                cout <<tokens.size()  <<endl;


                ssOneLine >> temp;//f
                std::string vertexStr;
                for (int i = 0; i < tokens.size(); ++i)
                {
                    ssOneLine >> vertexStr; //todo
                    size_t pos = vertexStr.find_first_of('/');
                    std::string positionIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1);
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
                    VertexDefine vd;
                    vd.positionIndex = atoi(positionIndexStr.c_str()) - 1;
                    vd.texcoordIndex = atoi(texcoordIndexStr.c_str()) - 1;
                    vd.normalIndex = atoi(normalIndexStr.c_str()) - 1;
                    //trim the same vertice
                    int nCurrentVertexIndex = -1;
                    size_t nCurrentVerticeCount = vertices.size();
//                        cout << "vertices.size()"<< vertices.size() << endl;

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
                    faces.push_back(nCurrentVertexIndex);
                }
            }

        }
    }
    int vertexCount = (int)vertices.size();
    VertexData*vertexes = new VertexData[vertexCount];
    for (int  i = 0; i < vertexCount; ++i)
    {
        memcpy(vertexes[i].position,positions[vertices[i].positionIndex].v,sizeof(float)*3);
        memcpy(vertexes[i].texcoord, texcoords[vertices[i].texcoordIndex].v, sizeof(float) * 2);
        memcpy(vertexes[i].normal, normals[vertices[i].normalIndex].v, sizeof(float) * 3);
    }

    //创建VBO
    glGenBuffers(1,&mVBO);//创建一个buffer
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);//指定BUFFER类型
    //将顶点数据上传至GPU
    glBufferData(GL_ARRAY_BUFFER,sizeof(VertexData)*vertexCount,vertexes,GL_STATIC_DRAW);
    for (int i = 0; i < vertexCount; i++) {
//        cout <<vertexes[i].position[0]<<endl;
    }
    glBindBuffer(GL_ARRAY_BUFFER,0);
    delete vertexes;

    //创建ebo
    mIndexCount = (int)faces.size();
    unsigned int *indexes = new unsigned int[mIndexCount];
    for (int  i = 0; i < mIndexCount; ++i)
    {
        indexes[i] = faces[i];
    }
    glGenBuffers(1,&mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*mIndexCount,indexes,GL_STATIC_DRAW);
    for (int i = 0; i < mIndexCount; i++) {
//        cout <<indexes[i] <<endl;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    delete indexes;

    delete fileContent;
}

void ObjModel::Bind(GLint posLoc, GLint texcoordLoc, GLint normalLoc)
{
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glEnableVertexAttribArray(posLoc);//启用顶点属性
    /*
    参数含义：
    第一个参数：GPU中顶点属性的引用
    第二个参数:因为顶点是一个向量,表示向量的维度
    第三个参数：每个维度数据的类型
    第四个参数：是否归一化
    第五个参数：每个顶点间的偏移量
    第六个参数：顶点数据的起始地址，因为用了VBO，所以起始地址为0
    实际起始地址跟顶点属性在结构体VertexData中的位置有关
    */
    glVertexAttribPointer(posLoc,3,GL_FLOAT,GL_FALSE,sizeof(VertexData),0);

    glEnableVertexAttribArray(texcoordLoc);//启用纹理属性
    glVertexAttribPointer(texcoordLoc,2,GL_FLOAT,GL_FALSE,sizeof(VertexData),
                          (void*)(sizeof(float)*3));//指定纹理坐标的起始地址

    glEnableVertexAttribArray(normalLoc);//启用法线属性
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                          (void*)(sizeof(float) * 5));//指定法线坐标的起始地址
    glBindBuffer(GL_ARRAY_BUFFER,0);


    this->loadMtlFile(this->directory);
//    cout << "mtls::"<<m_mtls[0]->Ka[0]<<endl;

}

void ObjModel::Draw(GLuint shadeID)
{
    vector<Texture> tempTextures;
//    vector<Texture> diffuseMaps=loadMaterialTextures("texture_diffuse");

    for (int i = 0; i < m_mtls.size(); i++) {
        glActiveTexture(GL_TEXTURE0+i);
//        glBindTexture(GL_TEXTURE_2D,textures[i].id);
        glBindTexture(GL_TEXTURE_2D, m_mtls[i]->texture);
        glUniform1i(glGetUniformLocation(shadeID,"texture_diffuse1"), 0 );
//        glUniform1i(glGetUniformLocation(shadeID,"texture_specular1"), 0 );
//        glUniform1i(glGetUniformLocation(shadeID,"texture_normal1"), 0 );

        glUniform4f(glGetUniformLocation(shadeID,"Ka"),m_mtls[i]->Ka[0],m_mtls[i]->Ka[1],m_mtls[i]->Ka[2],0.0f );
        glUniform4f(glGetUniformLocation(shadeID,"Kd"),m_mtls[i]->Kd[0],m_mtls[i]->Ka[1],m_mtls[i]->Kd[2],0.0f );
        glUniform4f(glGetUniformLocation(shadeID,"Ks"),m_mtls[i]->Ks[0],m_mtls[i]->Ka[1],m_mtls[i]->Ks[2],0.0f );

    }


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glDrawElements(GL_TRIANGLES,mIndexCount,GL_UNSIGNED_INT,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

vector<Texture> ObjModel::loadMaterialTextures(  string typeName){
    vector<Texture> textures;

}

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
char* ObjModel:: LoadFileContent(string filename) {
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



void ObjModel::loadFromFile(string objfile, string mtlfile)
{
    loadMtlFile(mtlfile);
//    loadObjFile(objfile);
//    transToVAO();
}
void ObjModel::loadMtlFile(string filename)
{
//    cout <<"filename" <<filename+"/capsule.mtl"<< endl;
//    cout <<"filename" <<filename+"/muro.mtl"<< endl;
    ifstream f;
    f.open(filename+"/muro.mtl", ios::in);
//    f.open(filename+"/capsule.mtl", ios::in);

    if (!f)
    {
//        cout << "Error: Mtl File cannot be opened!";
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
            Material* tMtl = new Material();

            tMtl->mtlName = ls[1];
            m_mtls.push_back(tMtl);  // 获得一个新的材质
//            cout << m_mtls.size() << endl;
            index = m_mtls.size() - 1;
        }

        if (ls[0] == "Ns")
        {
            int i;
            for (i = 0; i < ls[1].length(); i++)
                word[i] = ls[1][i];
            word[i] = '\0';
            m_mtls[index]->Ns = strtod(word,NULL);
        }
        if (ls[0] == "Ka")
        {
            m_mtls[index]->Ka[0] = stringToNum<double>(ls[1]);
            m_mtls[index]->Ka[1] = stringToNum<double>(ls[2]);
            m_mtls[index]->Ka[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "Kd")
        {
            m_mtls[index]->Kd[0] = stringToNum<double>(ls[1]);
            m_mtls[index]->Kd[1] = stringToNum<double>(ls[2]);
            m_mtls[index]->Kd[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "Ks")
        {
            m_mtls[index]->Ks[0] = stringToNum<double>(ls[1]);
            m_mtls[index]->Ks[1] = stringToNum<double>(ls[2]);
            m_mtls[index]->Ks[2] = stringToNum<double>(ls[3]);
        }
        if (ls[0] == "map_Kd")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  "map_Kd imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (directory+"/"+imgPath).c_str();
            m_mtls[index]->texture = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        if (ls[0] == "bump")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  " bump imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (directory+"/"+imgPath).c_str();
            m_mtls[index]->texture_bump = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        if (ls[0] == "map_Ks")
        {
            string imgPath = ls[1];
            //QString imgPath = "./res/obj/car1/"+strList[1];
//            cout <<  "map_Ks imgPath:"<<directory+"/"+imgPath <<endl;

            int x,y,n;
            const char * texture_url = (directory+"/"+imgPath).c_str();
            m_mtls[index]->texture_ks = loadTexture2D(texture_url, x, y, n, GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR);

        }
        ls.clear();

    }
}
