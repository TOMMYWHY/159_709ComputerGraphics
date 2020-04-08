#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Sphere.hpp"

#include "c3ga/c3gaTools.hpp"

namespace glimac {
    // Sphere::Sphere(const c3ga::Mvec<GLfloat> &radiusVector, const GLuint64 latitude, const GLuint64 longitude) : 
    // radiusVector(radiusVector), latitude(latitude), longitude(longitude) {};
        
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Sphere::Sphere(const GLfloat radius, const GLfloat Tx, const GLfloat Ty, const GLfloat Tz, const GLsizei discLat, const GLsizei discLong):
        vertexCount(0),longitude(discLong), latitude(discLat), posX(Tx), posY(Ty), posZ(Tz) {
        build(radius, latitude, longitude); // Construction (voir le .cpp)
        //buildC3GA();
    };

    Sphere::~Sphere(){}

    void Sphere::build(GLfloat radius, GLsizei discLat, GLsizei discLong) {
        GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
        GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;
        
        
        
        // Construit l'ensemble des vertex
        for(GLsizei j = 0; j <= discLong; ++j) {
            GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
            GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);
            
            for(GLsizei i = 0; i <= discLat; ++i) {
                ShapeVertex vertex;
                
                vertex.texCoords.x = i * rcpLat;
                vertex.texCoords.y = 1.f - j * rcpLong;

                vertex.normal.x = sin(i * dPhi) * cosTheta;
                vertex.normal.y = sinTheta;
                vertex.normal.z = cos(i * dPhi) * cosTheta;
                
                vertex.position = radius * vertex.normal;

                vertex.position.x = vertex.position.x + posX;
                vertex.position.y = vertex.position.y + posY;
                vertex.position.z = vertex.position.z + posZ;
                
                data.push_back(vertex);
            }
        }

        vertexCount = discLat * discLong * 6;
        for(GLsizei j = 0; j < discLong; ++j) {
            GLsizei offset = j * (discLat + 1);
            for(GLsizei i = 0; i < discLat; ++i) {
                vertices.push_back(data[offset + i]);
                vertices.push_back(data[offset + (i + 1)]);
                vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
                vertices.push_back(data[offset + i]);
                vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
                vertices.push_back(data[offset + i + discLat + 1]);
            }
        }
    }

    void Sphere::updatePosition(glm::vec3 diff){
        for(auto vertex : data){
            vertex.position.x = vertex.position.x + diff.x;
            vertex.position.y = vertex.position.y + diff.y;
            vertex.position.z = vertex.position.z + diff.z;
        }
        for(GLsizei j = 0; j < longitude; ++j) {
            GLsizei offset = j * (latitude + 1);
            for(GLsizei i = 0; i < latitude; ++i) {
                vertices.push_back(data[offset + i]);
                vertices.push_back(data[offset + (i + 1)]);
                vertices.push_back(data[offset + latitude + 1 + (i + 1)]);
                vertices.push_back(data[offset + i]);
                vertices.push_back(data[offset + latitude + 1 + (i + 1)]);
                vertices.push_back(data[offset + i + latitude + 1]);
            }
        }
    };


    const ShapeVertex* Sphere::getDataPointer() const {
        return &vertices[0];
    }
            
    GLsizei Sphere::getVertexCount() const {
        return vertexCount;
    }

    c3ga::Mvec<float> Sphere::getSphere() {
        return s;
    }

    void Sphere::setSphere(c3ga::Mvec<float> sph) {
        s = sph;
    }

    std::list<c3ga::Mvec<float>> Sphere::getCoordsphere() {
        return coordsphere;
    }
}
