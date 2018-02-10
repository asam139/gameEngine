//
// Created by Saul Moreno Abril on 05/02/2018.
//

#include "BoxCollider.h"
#include "GameObject.h"

#include <iostream>

const unsigned int _cornersSize = 8;
static glm::vec3 _corners[] = {
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f)
};

CLASS_DEFINITION(Collider, BoxCollider)

BoxCollider::BoxCollider( std::string && initialValue, GameObject *owner) : Collider( std::move( initialValue ), owner) {
    _size = glm::vec3(1.0f);
}

void BoxCollider::setSize(glm::vec3 size) {
    _size = size;
}

glm::vec3 BoxCollider::getSize(){
    return _size;
}

bool BoxCollider::collision(Collider *collider) {
    if (IsClassType(this->Type)) {
        BoxCollider* otherBoxCollider = (BoxCollider*)collider;

        AABB target = getAABB();
        AABB other = otherBoxCollider->getAABB();
        return (target.minVec.x <= other.maxVec.x && target.maxVec.x >= other.minVec.x) &&
               (target.minVec.y <= other.maxVec.y && target.maxVec.y >= other.minVec.y) &&
               (target.minVec.z <= other.maxVec.z && target.maxVec.z >= other.minVec.z);

        /*return(target.maxVec.x > other.minVec.x  &&
               target.minVec.x < other.maxVec.x &&
               target.maxVec.y > other.minVec.y &&
               target.minVec.y < other.maxVec.y &&
               target.maxVec.z > other.minVec.z &&
               target.minVec.z < other.maxVec.z);*/
    }

    return false;
};

BoxCollider::AABB BoxCollider::getAABB() {
    Transform& transform = getGameObject().getTransform();
    glm::vec3 finalPos  = transform.getWorldPosition() + _center;
    glm::vec3 otherHalfSize = transform.getScale() * _size;

    //std::cout << "FinalPos: x->" << finalPos.x << " FinalPos: y->" << finalPos.y << " FinalPos: z->" << finalPos.z << std::endl;

    // Get minVector and maxVector
    glm::vec3 corner = finalPos + _corners[0] * otherHalfSize;
    glm::vec3 minV = corner; glm::vec3 maxV = corner;
    for (int i = 0; i < _cornersSize; ++i) {
        glm::vec3 corner = finalPos + _corners[i] * otherHalfSize;
        float l = glm::length2(corner);
        if (l < glm::length2(minV)) {
            minV = corner;
        }

        if (l > glm::length2(maxV)) {
            maxV = corner;
        }
    }

    AABB aabb;
    aabb.minVec = minV;
    aabb.maxVec = maxV;

    //std::cout << "Min: x->" << minV.x << " Min: y->" << minV.y << " Min: z->" << minV.z << std::endl;
    //std::cout << "Max: x->" << maxV.x << " Max: y->" << maxV.y << " Man: z->" << maxV.z << std::endl;
    return aabb;
};



