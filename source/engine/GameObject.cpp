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
        renderer->render(projection, view, cameraPos, lightPos, light);
    }
}

void GameObject::collide(Collider* collider) {
    
}


