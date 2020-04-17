//
// Created by Tommy on 2020/4/16.
//

#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 position,glm::vec3 angles,glm::vec3 color):
Position(position),
Angles(angles),
Color(color)
{
    this->UpdateDirection();
}

void LightDirectional::UpdateDirection(){
    this->Direction = glm::vec3(0,0,1.0f);
    this->Direction = glm::rotateZ(this->Direction,this->Angles.z);
    this->Direction = glm::rotateX(this->Direction,this->Angles.x);
    this->Direction = glm::rotateY(this->Direction,this->Angles.y);
    this->Direction = -1.0f * this->Direction;
}

LightDirectional::~LightDirectional() {

}
