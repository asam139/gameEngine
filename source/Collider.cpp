//
// Created by Saul Moreno Abril on 05/02/2018.
//

#include "Collider.h"

CLASS_DEFINITION(Component, Collider)

Collider::Collider( std::string && initialValue, GameObject *owner) : Component( std::move( initialValue ), owner) {

}