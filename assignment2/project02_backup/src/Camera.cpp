//
// Created by Tommy on 2020/4/15.
//

#include "Camera.h"





Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {
    this->Position = position;
    this->WorldUp = worldup;
    this->Forward = glm::normalize(target-position);
    this->Right = glm::normalize(glm::cross(this->Forward,this->WorldUp));// have vec3
    this->Up = glm::normalize(glm::cross(this->Forward,this->Right));
}


Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
    this->Pitch = pitch;
    this->Yaw = yaw;

    this->Position = position;
    this->WorldUp = worldup;
    this->Forward.x = glm::cos( this->Pitch) * glm::sin( this->Yaw);
    this->Forward.y = glm::sin( this->Pitch) ;
    this->Forward.z = glm::cos( this->Pitch) * glm::cos( this->Yaw);;
    this->Right = glm::normalize(glm::cross(this->Forward,this->WorldUp));// have vec3
    this->Up = glm::normalize(glm::cross(this->Right,this->Forward));

}

Camera::~Camera() {

}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->Position,this->Position + this->Forward, this->WorldUp);
//    return glm::lookAt(this->Position,this->Position + this->Forward, this->Up);
}

void Camera::updateCameraVectors() {
    this->Forward.x = glm::cos(this->Pitch) * glm::sin(this->Yaw);
    this->Forward.y = glm::sin(this->Pitch) ;
    this->Forward.z = glm::cos(this->Pitch) * glm::cos(this->Yaw);
    this->Right = glm::normalize(glm::cross(this->Forward,this->WorldUp));// have vec3
    this->Up = glm::normalize(glm::cross(this->Right,this->Forward));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
    this->Pitch -= deltaY * this->Sense;
    this->Yaw -= deltaX * this->Sense;
    this->updateCameraVectors();

}

void Camera::updateCameraPosition() {
    this-> Position += this->Forward * this->speedZ *  this->Sense
            + this->Right * this->speedX * this->Sense
            + this->Up * this->speedY * this->Sense;

}

