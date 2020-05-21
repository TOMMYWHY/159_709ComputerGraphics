//
// Created by Tommy on 2020/5/21.
//

#ifndef OPENGL_DEMO_OBJMODEL_H
#define OPENGL_DEMO_OBJMODEL_H

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>





class ObjModel {


public:

    bool loadOBJ(
            const char * path,
            std::vector<glm::vec3> & out_vertices,
            std::vector<glm::vec2> & out_uvs,
            std::vector<glm::vec3> & out_normals
    ){
        printf("Loading OBJ file %s...\n", path);

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;


        FILE * file = fopen(path, "r");
        if( file == NULL ){
            printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
            getchar();
            return false;
        }

        while( 1 ){

            char lineHeader[256];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break; // EOF = End Of File. Quit the loop.

            // else : parse lineHeader

            if ( strcmp( lineHeader, "v" ) == 0 ){
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                cout <<  vertex.x<<","<< vertex.y << ","<< vertex.z<<endl;
                temp_vertices.push_back(vertex);
            }else if ( strcmp( lineHeader, "vt" ) == 0 ){
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y );
                uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
                temp_uvs.push_back(uv);
            }else if ( strcmp( lineHeader, "vn" ) == 0 ){
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                temp_normals.push_back(normal);
            }else if ( strcmp( lineHeader, "f" ) == 0 ){
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if (matches != 9){
                    printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                    fclose(file);
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }else{
                // Probably a comment, eat up the rest of the line
                char stupidBuffer[1000];
                fgets(stupidBuffer, 1000, file);
            }

        }

        // For each vertex of each triangle
        for( unsigned int i=0; i<vertexIndices.size(); i++ ){

            // Get the indices of its attributes
            unsigned int vertexIndex = vertexIndices[i];
            unsigned int uvIndex = uvIndices[i];
            unsigned int normalIndex = normalIndices[i];

            // Get the attributes thanks to the index
            glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
            glm::vec2 uv = temp_uvs[ uvIndex-1 ];
            glm::vec3 normal = temp_normals[ normalIndex-1 ];

            // Put the attributes in buffers
            out_vertices.push_back(vertex);
            out_uvs     .push_back(uv);
            out_normals .push_back(normal);

        }
        fclose(file);
        return true;
    }


    vector<vector<GLfloat>>vSets;//存放顶点(x,y,z)坐标
//    vector<glm::vec3>vSets;//存放顶点(x,y,z)坐标
    vector<vector<GLint>>fSets;//存放面的三个顶点索引
    void ObjLoader(string filename){
        string line;
        fstream f;
        f.open(filename, ios::in);
        if (!f.is_open()){
            cout << "Something Went Wrong When Opening Objfiles" << endl;
        }
        while (!f.eof()){
            getline(f, line);//拿到obj文件中一行，作为一个字符串
            vector<string>parameters;
            string tailMark = " ";
            string ans = "";

            line = line.append(tailMark);
            for (int i = 0; i < line.length(); i++) {
                char ch = line[i];
                if (ch != ' ') {
                    ans+=ch;
                }
                else {
                    parameters.push_back(ans); //取出字符串中的元素，以空格切分
                    ans = "";
                }
            }
            //cout << parameters.size() << endl;
            if(parameters.size() == 4 && parameters[0] == "v"){
                vector<GLfloat>Point;
                for (int i = 1; i < 4; i++) {   //从1开始，将顶点的xyz三个坐标放入顶点vector
                    GLfloat xyz = atof(parameters[i].c_str());
                    Point.push_back(xyz);
                }
                vSets.push_back(Point);
            }else if(parameters.size() == 5 && parameters[0] == "f"){
//                vector<GLint>vIndexSets;
                vector<int>Face;

                /*for (int i = 1; i < 4; i++){
                    string x = parameters[i];
                    string ans = "";
                    for (int j = 0; j < x.length(); j++) {   //跳过‘/’
                        char ch = x[j];
                        if (ch != '/') {
                            ans += ch;
                        }
                        else {
                            break;
                        }
                    }
                    GLint index = atof(ans.c_str());
                    index = index--;//因为顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
                    vIndexSets.push_back(index);
                }*/
                for (int i = 1; i < 5; i++) {   //从1开始，将顶点的xyz三个坐标放入顶点vector

                    GLfloat face_point = atof(parameters[i].c_str());
                    Face.push_back(face_point);
                }
                fSets.push_back(Face);
            }



           /* if (parameters.size() != 4) {
                cout << "the size is not correct" << endl;
            }
            else {
                if (parameters[0] == "v") {   //如果是顶点的话
                    vector<GLfloat>Point;
//                    glm::vec3 Point;
                    for (int i = 1; i < 4; i++) {   //从1开始，将顶点的xyz三个坐标放入顶点vector
                        GLfloat xyz = atof(parameters[i].c_str());
//                        cout << atof(parameters[i].c_str())<<endl;
                        Point.push_back(xyz);
                    }
                    vSets.push_back(Point);
                }

                else if (parameters[0] == "f") {   //如果是面的话，存放三个顶点的索引
                    vector<GLint>vIndexSets;
                    for (int i = 1; i < 4; i++){
                        string x = parameters[i];
                        string ans = "";
                        for (int j = 0; j < x.length(); j++) {   //跳过‘/’
                            char ch = x[j];
                            if (ch != '/') {
                                ans += ch;
                            }
                            else {
                                break;
                            }
                        }
                        GLint index = atof(ans.c_str());
                        index = index--;//因为顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
                        vIndexSets.push_back(index);
                    }
                    fSets.push_back(vIndexSets);
                }
            }*/
        }
        f.close();

    };

};


#endif //OPENGL_DEMO_OBJMODEL_H
