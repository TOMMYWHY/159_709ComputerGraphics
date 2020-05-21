//
// Created by Tommy on 2020/4/16.
//

#ifndef OPENGL_DEMO_LIGHTPOINT_H
#define OPENGL_DEMO_LIGHTPOINT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightPoint {
public:
    LightPoint(glm::vec3 position,glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
    ~LightPoint();

    glm::vec3 Position;
    glm::vec3 Color;

};


#endif //OPENGL_DEMO_LIGHTPOINT_H
