//
// Created by Saul Moreno Abril on 17/01/2018.
//

#include "GameObject.h"

#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject() {
    _transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    _transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    _transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

    configuration();
}

GameObject::~GameObject() {

}

void GameObject::configuration() {

}


void GameObject::setPosition(glm::vec3 position) {
    _transform.position = position;
}

glm::vec3 GameObject::getPosition() const {
    return _transform.position;
}

void GameObject::setRotation(glm::vec3 rotation) {
    _transform.rotation = rotation;
}

glm::vec3 GameObject::getRotation() const {
    return _transform.rotation;
}

void GameObject::setScale(glm::vec3 scale) {
    _transform.scale = scale;
}

glm::vec3 GameObject::getScale() const {
    return _transform.scale;
}

glm::mat4 GameObject::getModel() const {
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

void GameObject::setRenderer(std::shared_ptr<Renderer> renderer) {
    _renderer = renderer;
}

Renderer* GameObject::getRenderer() const {
    return _renderer.get();
}

void GameObject::display(const glm::mat4 projection, const glm::mat4 view, const glm::vec3 cameraPos, const glm::vec3 lightPos, const Light& light) const {
    if (_renderer) {
        glm::mat4 model = getModel();
        glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));

        Shader* shader = _renderer->getMaterial()->getShader();
        shader->set("view", view);
        shader->set("projection", projection);
        shader->set("model", model);
        shader->set("normal_mat", normalMat);
        shader->set("view_position", cameraPos);

        shader->set("light.position", lightPos);
        shader->set("light.ambient", light.getAmbientColor());
        shader->set("light.diffuse", light.getDiffuseColor());
        shader->set("light.specular", light.getSpecularColor());

        _renderer->render();
    }
}


