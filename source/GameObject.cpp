//
// Created by Saul Moreno Abril on 17/01/2018.
//

#include "GameObject.h"


GameObject::GameObject() {

}

GameObject::~GameObject() {

}

int GameObject::getIndecesSize() const {
    return _indicesSize;
}

uint32_t GameObject::getVAO() const{
    return _VAO;
}