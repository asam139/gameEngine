//
// Created by Saul Moreno Abril on 16/01/2018.
//

#include "Camera.h"

Camera::Camera() {
    _position = glm::vec3(0.f, 0.f, 0.f);
    _worldUp = glm::vec3(0.f, 1.f, 0.f),
    _yaw = kYaw;
    _pitch = kPitch;
    _fov = kFov;

    updateCameraVectors();
}

Camera::~Camera(){

}

Camera::Camera(const glm::vec3 position, const glm::vec3 up, const float yaw, const float pitch) {
    _position = position;
    _worldUp = up;
    _yaw = yaw;
    _pitch = pitch;
    _fov = kFov;
    updateCameraVectors();
}

Camera::Camera(const float posX, const float posY, const float posZ, const float upX, const float upY, const float upZ,
               const float yaw, const float pitch) {
    _position = glm::vec3(posX, posY, posZ);
    _worldUp =  glm::vec3(upX, upY, upZ);;
    _yaw = yaw;
    _pitch = pitch;
    _fov = kFov;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}

float Camera::getFOV() const {
    return _fov;
}

glm::vec3 Camera::getPosition() const {
    return _position;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

void Camera::handleKeyboard(Movement direction, const float deltaTime) {
    if (direction == Movement::None) {
        return;
    }

    float dS = kSpeed * deltaTime;

    if (direction & Movement::Forward) {
        _position += _front * dS;
    } else if (direction & Movement::Backward) {
        _position -= _front * dS;
    }

    if (direction & Movement::Right) {
        _position += _right * dS;
    } else if (direction & Movement::Left) {
        _position -= _right * dS;
    }
}

void Camera::handleMouseMovement(const float xOffset, const float yOffset, const bool constrainPitch) {
    float s_xOffset = xOffset * kSensitivity;
    float s_yOffset = yOffset * kSensitivity;


    _yaw += s_xOffset;
    _pitch += s_yOffset;

    // Constraints for the pitch
    if (_pitch > kMaxPitch) {
        _pitch = kMaxPitch;
    }
    if (_pitch < kMinPitch) {
        _pitch = kMinPitch;
    }

    updateCameraVectors();
}

void Camera::handleMouseScroll(const float yOffset) {
    if (_fov >= kMinFov && _fov <= kMaxFov) {
        _fov -= yOffset;
    }

    if (_fov <= kMinFov) {
        _fov = kMinFov;
    }

    if (_fov >= kMaxFov) {
        _fov = kMaxFov;
    }
}


