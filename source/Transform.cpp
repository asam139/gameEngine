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
}

glm::vec3 Transform::getPosition() const {
    return _position;
}

void Transform::setRotation(glm::quat rotation) {
    _rotation = rotation;
}

void Transform::setRotation(glm::vec3 eulerAngles) {
    _rotation = glm::quat(eulerAngles);
}

void Transform::setRotation(float rotationAngle, glm::vec3 rotationAxis) {
    _rotation = glm::angleAxis(rotationAngle, rotationAxis);
}

glm::quat Transform::getRotation() const {
    return _rotation;
}

void Transform::setScale(glm::vec3 scale) {
    _scale = scale;
}

glm::vec3 Transform::getScale() const {
    return _scale;
}

glm::mat4 Transform::getModel() const {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    model = model * glm::toMat4(_rotation);
    model = glm::scale(model, _scale);

    return _parentModel * model;
}

void Transform::setParentModel(glm::mat4 parentModel) {
    _parentModel = parentModel;
    dirty = false;
}

glm::mat4 Transform::getParentModel() {
    return _parentModel;
}