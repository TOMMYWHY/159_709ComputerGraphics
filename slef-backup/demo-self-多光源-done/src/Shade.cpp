//
// Created by Tommy on 2020/4/15.
//

#include "Shade.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
Shade::Shade(const char* vertexPath, const char* fragmentPath) {
    ifstream vertexFile;
    ifstream fragmentFile;
    stringstream vertexSStream;
    stringstream fragmentSStream;

    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);

    try {
        if(!vertexFile.is_open()||!fragmentFile.is_open()){
            throw "file open fail";
        }
        vertexSStream << vertexFile.rdbuf();
        fragmentSStream << fragmentFile.rdbuf();
        this->vertexString = vertexSStream.str();
        this->fragmentString = fragmentSStream.str();
        this->vertexSource = this->vertexString.c_str();
        this->fragmentSource = this->fragmentString.c_str();
//        cout << vertexSource <<endl;
//        cout << fragmentSource <<endl;
        GLuint vertex ,fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&this->vertexSource,NULL);
        glCompileShader(vertex);
        this->checkCompileErrors(vertex,"VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&this->fragmentSource,NULL);
        glCompileShader(fragment);
        this->checkCompileErrors(fragment,"FRAGMENT");


        this->ID = glCreateProgram();
        glAttachShader(this->ID,vertex);
        glAttachShader(this->ID,fragment);
        glLinkProgram(this->ID);
        this->checkCompileErrors(this->ID,"PROGRAM");


        glDeleteShader(vertex);
        glDeleteShader(fragment);


    }catch (const std::exception &ex){
        printf(ex.what());
    }

}

Shade::~Shade() {

}

void Shade::use(){
    glUseProgram(ID);
}

void Shade::test() {
    std::cout<<"testing....." <<std::endl;
}

void Shade::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
