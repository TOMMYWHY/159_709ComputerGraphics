//
// Created by Tommy on 2020/4/12.
//

#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec4 _position,glm::vec4 _angles,glm::vec4 _color):
    position(_position),
    angles(_angles),
    color(_color)
{
    UpdateDirection();
}

void LightDirectional::UpdateDirection( ){
    direction = glm::vec4(0.0f,0.0f,-1.0f,1.0f);
    direction = glm::rotateZ(direction, angles.z);
    direction = glm::rotateX(direction, angles.x);
    direction = glm::rotateY(direction, angles.y);

    direction = -1.0f*direction;

};

LightDirectional::~LightDirectional() {}