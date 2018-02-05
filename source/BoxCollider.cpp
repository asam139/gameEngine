//
// Created by Saul Moreno Abril on 05/02/2018.
//

#include "BoxCollider.h"

CLASS_DEFINITION(Collider, BoxCollider)

BoxCollider::BoxCollider( std::string && initialValue, GameObject *owner) : Collider( std::move( initialValue ), owner) {

}