//
// Created by Tommy on 2020/4/16.
//

#ifndef OPENGL_DEMO_LIGHTSPOT_H
#define OPENGL_DEMO_LIGHTSPOT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightSpot {

public:
    LightSpot(glm::vec3 position,glm::vec3 angles,glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
    ~LightSpot();

    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec3 Angles;
    glm::vec3 Direction = glm::vec3(0,0,1.0f);
    float cosPhyInner =0.9f;
    float cosPhyOuter = 0.85f;


    void UpdateDirection();

};


#endif //OPENGL_DEMO_LIGHTSPOT_H