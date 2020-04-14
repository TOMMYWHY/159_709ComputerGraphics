//
// Created by Tommy on 2020/4/12.
//

#include "LightPoint.h"


LightPoint::LightPoint(glm::vec4 _position,glm::vec4 _angles,glm::vec4 _color):
        position(_position),
        angles(_angles),
        color(_color)
{
     constant =1.0f;
     linear = 0.09f;
     quadratic =0.032f;
}


LightPoint::~LightPoint() {}