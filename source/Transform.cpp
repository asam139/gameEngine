//
// Created by Saul Moreno Abril on 04/02/2018.
//

#include "Transform.h"

CLASS_DEFINITION(Component, Transform)

Transform::Transform( std::string && initialValue, GameObject *owner) : Component( std::move( initialValue ), owner) {
    _position = glm::vec3(0.0f);
    _rotation = glm::vec3(0.0f);
    _scale = glm::vec3(1.0f);
}


void Transform::setPosition(glm::vec3 position) {
    _position = position;
}

glm::vec3 Transform::getPosition() const {
    return _position;
}

void Transform::setRotation(glm::vec3 rotation) {
    _rotation = rotation;
}

glm::vec3 Transform::getRotation() const {
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
    model = glm::rotate(model, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, _scale);

    return model;
}