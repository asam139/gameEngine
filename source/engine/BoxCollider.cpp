//
// Created by Saul Moreno Abril on 05/02/2018.
//

#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"

#include <iostream>
#include <engine/SphereCollider.h>

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
    if (collider->IsClassType(BoxCollider::Type)) {
        BoxCollider* otherBoxCollider = (BoxCollider*)collider;

        AABB target = getAABB();
        AABB other = otherBoxCollider->getAABB();
        return (target.minVec.x <= other.maxVec.x && target.maxVec.x >= other.minVec.x) &&
               (target.minVec.y <= other.maxVec.y && target.maxVec.y >= other.minVec.y) &&
               (target.minVec.z <= other.maxVec.z && target.maxVec.z >= other.minVec.z);

    } else if (collider->IsClassType(SphereCollider::Type)) {
        SphereCollider* otherCollider = (SphereCollider *)collider;
        SphereCollider::SSSS ssss = otherCollider->getSSSS();

        BoxCollider::AABB aabb = getAABB();
        float x = fmaxf(aabb.minVec.x, fminf(ssss.pos.x, aabb.maxVec.x));
        float y = fmaxf(aabb.minVec.y, fminf(ssss.pos.y, aabb.maxVec.y));
        float z = fmaxf(aabb.minVec.z, fminf(ssss.pos.z, aabb.maxVec.z));

        // this is the same as isPointInsideSphere
        float distance = sqrtf((x - ssss.pos.x) * (x - ssss.pos.x) +
                               (y - ssss.pos.y) * (y - ssss.pos.y) +
                               (z - ssss.pos.z) * (z - ssss.pos.z));

        return distance < ssss.radius;
    }

    return false;
};

BoxCollider::AABB BoxCollider::getAABB() {
    Transform& transform = getGameObject().getTransform();
    glm::vec3 finalPos  = transform.getWorldPosition() + _center;
    glm::vec3 otherHalfSize = transform.getScale() * _size;

    //std::cout << "FinalPos: x->" << finalPos.x << " FinalPos: y->" << finalPos.y << " FinalPos: z->" << finalPos.z << std::endl;

    // Get minVector and maxVector
    glm::vec3 corner = glm::vec3(0.0f);
    glm::vec3 minV = finalPos + _corners[7] * otherHalfSize;
    glm::vec3 maxV = finalPos + _corners[0] * otherHalfSize;
    float l, lMin, lMax, lB;
    for (int i = 0; i < _cornersSize; ++i) {
        corner = finalPos + _corners[i] * otherHalfSize;
        l = glm::length2(corner);
        lMin = glm::length2(minV);
        lMax = glm::length2(maxV);
        lB = glm::length2(maxV-minV);

        if (l < lMin &&  glm::length2(maxV - corner) >  lB) {
            minV = corner;
        } else if (l > lMax && glm::length2(corner - minV) >  lB) {
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



