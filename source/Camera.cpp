//
// Created by Saul Moreno Abril on 16/01/2018.
//

#include "Camera.h"

#include <queue>

Camera::Camera() {
    _position = glm::vec3(0.f, 0.f, 0.f);
    _worldUp = glm::vec3(0.f, 1.f, 0.f);
    _yaw = kYaw;
    _pitch = kPitch;
    _fov = kFov;

    updateCameraVectors();
}

Camera::~Camera(){

}

Camera::Camera(const glm::vec3 position, const glm::vec3 up, const float pitch) {
    _position = position;
    _worldUp = up;
    _yaw = kYaw;
    _pitch = pitch;
    _fov = kFov;
    updateCameraVectors();
}

Camera::Camera(const float posX, const float posY, const float posZ, const float upX, const float upY, const float upZ,
               const float pitch) {
    _position = glm::vec3(posX, posY, posZ);
    _worldUp =  glm::vec3(upX, upY, upZ);;
    _yaw = kYaw;
    _pitch = pitch;
    _fov = kFov;
    updateCameraVectors();
}

void Camera::setAspect(float aspect) {
    _aspect = aspect;
}

float Camera::getAspect() {
    return _aspect;
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

void Camera::setMovementAxis(MovementAxis movementAxis) {
    _movementAxis = movementAxis;
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
    if (direction == MovementNone) {
        return;
    }

    float dS = kSpeed * deltaTime;

    glm::vec3 constraintsFront;
    constraintsFront.x = _movementAxis & MovementAxisX ? _front.x : 0.f;
    constraintsFront.y = _movementAxis & MovementAxisY ? _front.y : 0.f;
    constraintsFront.z = _movementAxis & MovementAxisZ ? _front.z : 0.f;
    constraintsFront = glm::normalize(constraintsFront);

    if (direction & MovementForward) {
        _position += constraintsFront * dS;
    } else if (direction & MovementBackward) {
        _position -= constraintsFront * dS;
    }

    if (direction & MovementRight) {
        _position += _right * dS;
    } else if (direction & MovementLeft) {
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


void Camera::render(GameObject& root, GameObject& lightObject) {
    glm::mat4 projection = glm::perspective(glm::radians(getFOV()), _aspect, 0.1f, 100.f);
    glm::mat4 view = getViewMatrix();
    glm::vec3 cameraPos = getPosition();

    ////////////////////////////////
    // Get Light
    auto& light = lightObject.GetComponent<Light>();
    glm::vec3 lightPos = lightObject.getTransform().getPosition();


    std::queue<GameObject*> Q;
    std::vector<std::shared_ptr<GameObject>>* children;

    Q.push(&root);
    while(!Q.empty()) {

        GameObject* gO = Q.front();
        glm::mat4 model = gO->getTransform().getModel();
        Q.pop();

        gO->display(projection, view, cameraPos, lightPos, light);

        children = &(gO->children);
        for (int i = 0; i < children->size(); ++i) {
            GameObject* child = (*children)[i].get();
            //if(gO->getTransform().dirty) {
                child->getTransform().setParentModel(model);
            //}
            Q.push(child);
        }
    }
}

