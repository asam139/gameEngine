//
// Created by Saul Moreno Abril on 11/02/2018.
//

#include "Pad.h"

Pad::Pad() : Cube () {

}

Pad::Pad(const glm::vec3 center, const float radius) : Cube(center, radius) {

}

void Pad::setMinX(float minX) {
    _minX = minX;
}

float Pad::getMinX() {
    return _minX;
}

void Pad::setMaxX(float maxX) {
    _maxX = maxX;
}

float Pad::getMaxX() {
    return _maxX;
}

void Pad::setVelocityX(float vX) {
    _velocityX = vX;
}

float Pad::getVelocityX() {
    return _velocityX;
}

void Pad::update(const float deltaTime) {
    glm::vec3 newPos = _transform->getPosition() + glm::vec3(deltaTime * _velocityX, 0.0f, 0.0f);
    if (newPos.x > _minX  && newPos.x < _maxX) {
        _transform->setPosition(newPos);
    }
}