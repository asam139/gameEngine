//
// Created by Saul Moreno Abril on 04/02/2018.
//

#include "Component.h"
#import "GameObject.h"


const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

bool Component::IsClassType(const std::size_t classType) const {
    return classType == Type;
}

GameObject& Component::getGameObject() const {
    return *_gameObject;
}