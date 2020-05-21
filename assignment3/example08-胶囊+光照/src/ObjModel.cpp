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



void ObjModel::Init(const char*modelFilePath)
{
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
                ssOneLine >> temp;//f
                std::string vertexStr;
                for (int i = 0; i < 3; ++i)
                {
                    ssOneLine >> vertexStr;
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



}

void ObjModel::Draw()
{
    vector<Texture> tempTextures;
    vector<Texture> diffuseMaps=loadMaterialTextures("texture_diffuse");

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
char* ObjModel:: LoadFileContent(const char *filename) {
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
