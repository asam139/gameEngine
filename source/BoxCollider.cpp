//
// Created by Saul Moreno Abril on 05/02/2018.
//

#include "BoxCollider.h"
#import "GameObject.h"

CLASS_DEFINITION(Collider, BoxCollider)

BoxCollider::BoxCollider( std::string && initialValue, GameObject *owner, glm::vec3 size) : Collider( std::move( initialValue ), owner) {
    _size = size;
}

void BoxCollider::setSize(glm::vec3 size) {
    _size = size;
}

glm::vec3 BoxCollider::getSize(){
    return _size;
}

bool BoxCollider::collision(Collider *collider) {
    if (IsClassType(this->Type)) {
        GameObject& otherGameObject = collider->getGameObject();
        Transform& otherTransform = otherGameObject.getTransform();
        glm::vec3 otherFinalPos  = otherTransform.getWorldPosition() + _center;
        glm::vec3 otherFinalSize = otherTransform.getScale() * _size;
        // Get 4 corners



        Transform& transform = getGameObject().getTransform();
        glm::vec3 finalPos  = transform.getWorldPosition() + _center;
        glm::vec3 finalSize = transform.getScale() * _size;
        // Get 4 corners and

    }
};
