#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

    struct ShapeVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL= 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

}
