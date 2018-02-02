//
// Created by Saul Moreno Abril on 17/01/2018.
//

#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject() {
    _transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    _transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    _transform.scale = glm::vec3(0.0f, 0.0f, 0.0f);

    configuration();
}

GameObject::~GameObject() {

}

void GameObject::configuration() {

}

void GameObject::setPosition(glm::vec3 position) {
    _transform.position = position;
}

glm::vec3 GameObject::getPosition() {
    return _transform.position;
}

void GameObject::setRotation(glm::vec3 rotation) {
    _transform.rotation = rotation;
}

glm::vec3 GameObject::getRotation() {
    return _transform.rotation;
}

void GameObject::setScale(glm::vec3 scale) {
    _transform.scale = scale;
}

glm::vec3 GameObject::getScale() {
    return _transform.scale;
}

glm::mat4 GameObject::getModel() {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, _transform.position);
    model = glm::rotate(model, _transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, _transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, _transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, _transform.scale);

    return model;
}

void GameObject::update(const float deltaTime) {

}


Renderer* GameObject::getRenderer() {
    return _renderer.get();
}