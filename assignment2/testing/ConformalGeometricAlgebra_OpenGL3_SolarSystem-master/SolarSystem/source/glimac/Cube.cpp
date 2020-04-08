#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

namespace glimac {

/** Generation dun cube avec 2 tirangles par face, chaque face 3 vertex **/ //a ameilorer avec un VIO par la suite 
/** face 0 --> Front
 *  face 1 --> back 
 *  face 2 --> right
 *  face 3 --> Left
 *  face 4 --> Up
 *  face 5 --> Donw
 **/

    void Cube::build(GLfloat size_c) {
        std::vector<ShapeVertex> data;

        ShapeVertex vertex;
        /** Front face **/
        /** First Triangle **/
        // 1
        vertex.texCoords = glm::vec2(0, 1);
        vertex.normal = glm::vec3(0, 0, 1);
        vertex.position = glm::vec3(0,0,0);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, 0, 1);
        vertex.position = glm::vec3(size_c,0,0);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, 0, 1);
        vertex.position = glm::vec3(0,size_c,0);;
        data.push_back(vertex);
        // triangle 2
        // 1
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, 0, 1);
        vertex.position = glm::vec3(0,size_c,0);;
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, 0, 1);
        vertex.position = glm::vec3(size_c,0,0);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(1, 0);
        vertex.normal = glm::vec3(0, 0, 1);
        vertex.position = glm::vec3(size_c,size_c,0);;
        data.push_back(vertex);
        
        /** Back face **/
        // triangle 3
        // 1
        vertex.texCoords = glm::vec2(0, 1);
        vertex.normal = glm::vec3(0, 0, -1);
        vertex.position = glm::vec3(0,0,-size_c);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, 0, -1);
        vertex.position = glm::vec3(0,size_c,-size_c);;
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, 0, -1);
        vertex.position = glm::vec3(size_c,0,-size_c);
        data.push_back(vertex);

        // triangle 4
        // 1
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, 0, -1);
        vertex.position = glm::vec3(0,size_c,-size_c);;
        data.push_back(vertex);
        //2
        vertex.texCoords = glm::vec2(1, 0);
        vertex.normal = glm::vec3(0, 0, -1);
        vertex.position = glm::vec3(size_c,size_c,-size_c);;
        data.push_back(vertex);

        //3
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, 0, -1);
        vertex.position = glm::vec3(size_c,0,-size_c);
        data.push_back(vertex);


        /** Right face **/
        // triangle 5
        // 1
        vertex.texCoords = glm::vec2(0, 1);
        vertex.normal = glm::vec3(1, 0, 0);
        vertex.position = glm::vec3(size_c,0,0);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(1, 0, 0);
        vertex.position = glm::vec3(size_c,0,-size_c);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(1, 0, 0);
        vertex.position = glm::vec3(size_c,size_c,0);
        data.push_back(vertex);

        // triangle 6
        // 1
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(1, 0, 0);
        vertex.position = glm::vec3(size_c,size_c,0);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(1, 0, 0);
        vertex.position = glm::vec3(size_c,0,-size_c);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(1, 0);
        vertex.normal = glm::vec3(1, 0, 0);
        vertex.position = glm::vec3(size_c,size_c,-size_c);
        data.push_back(vertex);

        //** Left face **/
        // triangle 7
        // 1
        vertex.texCoords = glm::vec2(0, 1);
        vertex.normal = glm::vec3(-1, 0, 0);
        vertex.position = glm::vec3(0,0,-size_c);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(-1, 0, 0);
        vertex.position = glm::vec3(0,0,0);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(-1, 0, 0);
        vertex.position = glm::vec3(0,size_c,-size_c);
        data.push_back(vertex);

        // triangle 8
        // 1
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(-1, 0, 0);
        vertex.position = glm::vec3(0,size_c,-size_c);
        data.push_back(vertex);
        // 2

        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(-1, 0, 0);
        vertex.position = glm::vec3(0,0,0);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(1, 0);
        vertex.normal = glm::vec3(-1, 0, 0);
        vertex.position = glm::vec3(0,size_c,0);
        data.push_back(vertex);

        /** Up face **/
        // triangle 9
        // 1
        vertex.texCoords = glm::vec2(0, 1);
        vertex.normal = glm::vec3(0, 1, 0);
        vertex.position = glm::vec3(size_c,size_c,0);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, 1, 0);
        vertex.position = glm::vec3(size_c,size_c,-size_c);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, 1, 0);
        vertex.position = glm::vec3(0,size_c,0);
        data.push_back(vertex);
        // triangle 10
        // 1
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, 1, 0);
        vertex.position = glm::vec3(0,size_c,0);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, 1, 0);
        vertex.position = glm::vec3(size_c,size_c,-size_c);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(1, 0);
        vertex.normal = glm::vec3(0, 1, 0);
        vertex.position = glm::vec3(0,size_c,-size_c);
        data.push_back(vertex);

        /** Down face **/
        // triangle 11
        // 1
        vertex.texCoords = glm::vec2(0, 1);
        vertex.normal = glm::vec3(0, -1, 0);
        vertex.position = glm::vec3(0,0,-size_c);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, -1, 0);
        vertex.position = glm::vec3(size_c,0,-size_c);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, -1, 0);
        vertex.position = glm::vec3(0,0,0);
        data.push_back(vertex);

        // triangle 12
        // 1
        vertex.texCoords = glm::vec2(0, 0);
        vertex.normal = glm::vec3(0, -1, 0);
        vertex.position = glm::vec3(0,0,0);
        data.push_back(vertex);
        // 2
        vertex.texCoords = glm::vec2(1, 1);
        vertex.normal = glm::vec3(0, -1, 0);
        vertex.position = glm::vec3(size_c,0,-size_c);
        data.push_back(vertex);
        // 3
        vertex.texCoords = glm::vec2(1, 0);
        vertex.normal = glm::vec3(0, -1, 0);
        vertex.position = glm::vec3(size_c,0,0);
        data.push_back(vertex);

        m_nVertexCount = 36;
        m_Vertices = data;
    }
}
