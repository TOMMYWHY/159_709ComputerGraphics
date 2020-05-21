//
// Created by Tommy on 2020/4/16.
//

#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 position, glm::vec3 angles, glm::vec3 color):
Position(position),
Angles(angles),
Color(color)
{

}

LightSpot::~LightSpot() {

}

void LightSpot::UpdateDirection() {

}
