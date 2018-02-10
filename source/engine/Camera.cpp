//
// Created by Saul Moreno Abril on 16/01/2018.
//

#include "Camera.h"

#include <queue>

CLASS_DEFINITION(Component, Camera)

Camera::Camera(std::string && initialValue, GameObject * owner) : Component( std::move( initialValue ), owner) {
    _worldUp = glm::vec3(0.f, 1.f, 0.f);
    _yaw = kYaw;
    _pitch = kPitch;
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
    glm::vec3 pos = getPosition();
    return glm::lookAt(pos, pos + _front, _up);
}

float Camera::getFOV() const {
    return _fov;
}

glm::vec3 Camera::getPosition() const {
    return getGameObject().getTransform().getWorldPosition();
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

    glm::vec3 pos = getGameObject().getTransform().getPosition();
    if (direction & MovementForward) {
        pos += constraintsFront * dS;
        getGameObject().getTransform().setPosition(pos);
    } else if (direction & MovementBackward) {
        pos -= constraintsFront * dS;
        getGameObject().getTransform().setPosition(pos);
    }

    if (direction & MovementRight) {
        pos += _right * dS;
        getGameObject().getTransform().setPosition(pos);
    } else if (direction & MovementLeft) {
        pos -= _right * dS;
        getGameObject().getTransform().setPosition(pos);
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
    glm::vec3 cameraPos = getGameObject().getTransform().getWorldPosition();

    ////////////////////////////////
    // Get Light
    auto light = lightObject.GetComponent<Light>();
    glm::vec3 lightPos = lightObject.getTransform().getPosition();


    std::queue<GameObject*> Q;
    std::vector<std::shared_ptr<GameObject>>* children;

    Q.push(&root);
    while(!Q.empty()) {

        GameObject* gO = Q.front();
        glm::mat4 model = gO->getTransform().getModel();
        Q.pop();

        if (!gO->isActive()) continue;

        gO->display(projection, view, cameraPos, lightPos, *light);

        children = &(gO->children);
        for (int i = 0; i < children->size(); ++i) {
            GameObject* child = (*children)[i].get();
            if(gO->getTransform().dirty) {
                child->getTransform().setParentModel(model);
            }
            Q.push(child);
        }
    }
}

