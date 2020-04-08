#include "glimac/FreeFlyCamera.hpp"
#include <iostream>
#include <math.h>

namespace glimac {

    FreeFlyCamera::FreeFlyCamera() : m_fDistance(5), m_fAngleX(0), m_fAngleY(0) {
    }

    FreeFlyCamera::~FreeFlyCamera() {
    }

    void FreeFlyCamera::moveFront(float delta) {
        m_fDistance += delta;
    }

    void FreeFlyCamera::rotateLeft(float degrees) {
        m_fAngleX = degrees / 180 * M_PI;
    }

    void FreeFlyCamera::rotateUp(float degrees){
        m_fAngleY = degrees / 180 * M_PI;
    }

    glm::mat4 FreeFlyCamera::getViewMatrix() const{
        glm::mat4 identity = glm::mat4(1.0); //Matrice Identité
        glm::mat4 matrixMoveFront = glm::translate(identity, glm::vec3(0.0f, 0.0f, -m_fDistance)); //Translation en z
        glm::mat4 matrixrotateLeft = glm::rotate(identity, m_fAngleX, glm::vec3(1, 0, 0)); //Axe x
        glm::mat4 matrixrotateUp = glm::rotate(identity, m_fAngleY, glm::vec3(0, 1, 0)); //Axe y
        return matrixMoveFront * matrixrotateLeft * matrixrotateUp;
    }

}