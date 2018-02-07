//
// Created by Saul Moreno Abril on 04/02/2018.
//

#include "Transform.h"

CLASS_DEFINITION(Component, Transform)

Transform::Transform( std::string && initialValue, GameObject *owner) : Component( std::move( initialValue ), owner) {
    _position = glm::vec3(0.0f);
    _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.f);
    _scale = glm::vec3(1.0f);

    _parentModel = glm::mat4(1.0f);

    dirty = true;
}


void Transform::setPosition(glm::vec3 position) {
    _position = position;
    dirty = true;
}

glm::vec3 Transform::getPosition() const {
    return _position;
}

void Transform::setRotation(glm::quat rotation) {
    _rotation = rotation;
    dirty = true;
}

void Transform::setRotation(glm::vec3 eulerAngles) {
    _rotation = glm::quat(eulerAngles);
    dirty = true;
}

void Transform::setRotation(float rotationAngle, glm::vec3 rotationAxis) {
    _rotation = glm::angleAxis(rotationAngle, rotationAxis);
    dirty = true;
}

glm::quat Transform::getRotation() const {
    return _rotation;
}

void Transform::setScale(glm::vec3 scale) {
    _scale = scale;
    dirty = true;
}

glm::vec3 Transform::getScale() const {
    return _scale;
}

void Transform::setParentModel(glm::mat4 parentModel) {
    _parentModel = parentModel;
    dirty = false;
}

glm::mat4 Transform::getParentModel() {
    return _parentModel;
}

glm::vec3 Transform::getWorldPosition() {
    glm::vec4 pos = glm::vec4(_position.x, _position.y, _position.z, 1.0f);
    return glm::vec3(_parentModel * pos);
}


glm::quat Transform::getWorldRotation() {
    glm::mat4 rotMat = glm::toMat4(_rotation);
    return glm::toQuat(_parentModel * rotMat);
}

glm::vec3 Transform::getForward() {
    glm::vec4 pos = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    return glm::normalize(glm::vec3(glm::rotate(getWorldRotation(), pos)));
}

glm::vec3 Transform::getUp() {
    glm::vec4 pos = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    return glm::normalize(glm::vec3(glm::rotate(getWorldRotation(), pos)));
}

glm::vec3 Transform::getRight() {
    glm::vec4 pos = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    return glm::normalize(glm::vec3(glm::rotate(getWorldRotation(), pos)));
}

glm::mat4 Transform::getModel() const {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    model = model * glm::toMat4(_rotation);
    model = glm::scale(model, _scale);

    return _parentModel * model;
}

