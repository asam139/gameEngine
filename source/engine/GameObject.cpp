//
// Created by Saul Moreno Abril on 17/01/2018.
//

#include "GameObject.h"

GameObject::GameObject() {
    AddComponent<Transform>("Transform", this);
    _transform = GetComponent<Transform>();

    configuration();
}

GameObject::~GameObject() {

}

void GameObject::configuration() {

}

void GameObject::setActive(bool active) {
    _active = active;
}

bool GameObject::isActive() {
    return _active;
}

Transform& GameObject::getTransform() {
    return *_transform;
}


///////////////////////////////////////////////////////
void GameObject::AddChild(std::shared_ptr<GameObject> gameObject_ptr) {
    children.push_back(gameObject_ptr);
}

//////////////////////////////////////////////////////

void GameObject::update(const float deltaTime) {

}

void GameObject::display(const glm::mat4 projection, const glm::mat4 view, const glm::vec3 cameraPos, const glm::vec3 lightPos, const Light& light) {
    auto renderer = GetComponent<Renderer>();
    if (renderer != nullptr) {
        glm::mat4 model = _transform->getModel();
        glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));

        Shader* shader = renderer->getMaterial()->getShader();
        shader->set("view", view);
        shader->set("projection", projection);
        shader->set("model", model);
        shader->set("normal_mat", normalMat);
        shader->set("view_position", cameraPos);

        shader->set("light.position", lightPos);
        shader->set("light.ambient", light.getAmbientColor());
        shader->set("light.diffuse", light.getDiffuseColor());
        shader->set("light.specular", light.getSpecularColor());

        renderer->render();
    }
}

void GameObject::collide(Collider* collider) {
    
}

