//
// Created by Tommy on 2020/4/15.
//

#ifndef OPENGL_DEMO_CAMERA_H
#define OPENGL_DEMO_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;

    float Pitch;
    float Yaw;
    float Sense = 0.001f;
    float speedZ = 0;
    float speedX= 0;
    float speedY= 0;

    Camera(glm::vec3 position,float pitch, float yaw,glm::vec3 worldup );

    glm::mat4 GetViewMatrix();
    void ProcessMouseMovement(float deltaX, float deltaY);
    void updateCameraPosition();
    ~Camera();

private:
    void updateCameraVectors();
};


#endif //OPENGL_DEMO_CAMERA_H
