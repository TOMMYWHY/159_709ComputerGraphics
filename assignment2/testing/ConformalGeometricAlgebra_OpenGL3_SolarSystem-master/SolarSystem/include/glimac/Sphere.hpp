#pragma once

#include <vector>

#include "common.hpp"

#include <c3ga/Mvec.hpp>

namespace glimac {

    // Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
    // Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
    class Sphere {

        public:
            // Constructor
            //Sphere(const c3ga::Mvec<GLfloat> &radiusVector, const GLuint64 longitude, const GLuint64 latitude);
            Sphere(const GLfloat radius = 1, const GLfloat Tx = 0, const GLfloat Ty = 0, const GLfloat Tz = 0, const GLsizei discLat = 16, const GLsizei discLong = 16);

            // Destructor
            ~Sphere();

            // Alloue et construit les données (implantation dans le .cpp)
            void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

            // Alloue et construit les données (implantation dans le .cpp)
            void updatePosition(glm::vec3 diff);

            // Renvoit le pointeur vers les données
            const ShapeVertex* getDataPointer() const;
            
            // Renvoit le nombre de vertex
            GLsizei getVertexCount() const;

            c3ga::Mvec<float> sphere(float Rsphere);
            c3ga::Mvec<float> getSphere();
            void setSphere(c3ga::Mvec<float> sph);
            std::list<c3ga::Mvec<float>> getCoordsphere();

        private:
        	c3ga::Mvec<float> s;
        	std::list<c3ga::Mvec<float>> coordsphere;
            std::vector<ShapeVertex> vertices;
            c3ga::Mvec<GLfloat> radiusVector;
            GLsizei vertexCount; // Nombre de sommets
            GLsizei latitude;
            GLsizei longitude;
            std::vector<ShapeVertex> data;

            float posX, posY, posZ;
      
    };
    
}