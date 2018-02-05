//
// Created by Saul Moreno Abril on 05/02/2018.
//

#include "Collider.h"

CLASS_DEFINITION(Component, Collider)

Collider::Collider( std::string && initialValue, GameObject *owner) : Component( std::move( initialValue ), owner) {

}

void Collider::setCenter(glm::vec3 center) {
    _center = center;
}

glm::vec3 Collider::getCenter() {
    return _center;
}
