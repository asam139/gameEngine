//
// Created by Saul Moreno Abril on 10/02/2018.
//

#include "Ball.h"

#include <glm/gtx/vector_angle.hpp>
#include <iostream>

Ball::Ball() : Sphere(){

}

Ball::Ball(const glm::vec3 center, const float radius) : Sphere(center, radius) {

}

void Ball::setVelocity(glm::vec3 velocity) {
    _velocity = velocity;
}

glm::vec3 Ball::getVelocity() {

}

void Ball::update(const float deltaTime) {
    glm::vec3 newPos = _transform->getPosition() + deltaTime * _velocity;
    _transform->setPosition(newPos);
}

void Ball::collide(Collider *collider) {
    GameObject* otherGO = &(collider->getGameObject());
    if (otherGO == leftWall || otherGO == rightWall) {
        _velocity.x = -_velocity.x;
    } else if (otherGO == upperWall) {
        _velocity.y = -_velocity.y;
    } else if (otherGO == ground) {
        _active = false;
    } else if (otherGO == pad) {
        glm::vec3 padPos = pad->getTransform().getWorldPosition();
        glm::vec3 ballPos = getTransform().getWorldPosition();
        glm::vec3 posDiff = glm::normalize(ballPos - padPos);
        float angle = glm::angle(posDiff, pad->getTransform().getUp());


        float module = glm::length(_velocity);
        float direction = padPos.x > ballPos.x ? -1.0f : 1.0f;
        _velocity.x = direction * module * sinf(angle);
        _velocity.y = module * cosf(angle);
    }
}