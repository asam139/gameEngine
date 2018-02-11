//
// Created by Saul Moreno Abril on 11/02/2018.
//

#include <engine/BoxCollider.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"


CLASS_DEFINITION(Collider, SphereCollider)

SphereCollider::SphereCollider( std::string && initialValue, GameObject *owner) : Collider( std::move( initialValue ), owner) {
    _radius = 1.0f;
}

void SphereCollider::setRadius(float radius) {
    _radius = radius;
}

float SphereCollider::getRadius() {
    return _radius;
}

bool SphereCollider::collision(Collider *collider) {
    if (collider->IsClassType(SphereCollider::Type)) {
        SphereCollider* otherCollider = (SphereCollider*)collider;
        Transform& otherTransform = otherCollider->getGameObject().getTransform();
        glm::vec3 otherSpherePos  = otherTransform.getWorldPosition() + otherCollider->getCenter();
        glm::vec3 otherSphereScale = otherTransform.getScale();
        float otherSRadius = fmaxf(fmaxf(otherSphereScale.x, otherSphereScale.y), otherSphereScale.z) * otherCollider->getRadius();

        Transform& transform = getGameObject().getTransform();
        glm::vec3 spherePos  = transform.getWorldPosition() + _center;
        glm::vec3 sphereScale = transform.getScale();
        float sRadius = fmaxf(fmaxf(sphereScale.x, sphereScale.y), sphereScale.z) * _radius;


        float distance = sqrtf((spherePos.x - otherSpherePos.x) * (spherePos.x - otherSpherePos.x) +
                                 (spherePos.y - otherSpherePos.y) * (spherePos.y - otherSpherePos.y) +
                                 (spherePos.z - otherSpherePos.z) * (spherePos.z - otherSpherePos.z));
        return distance < (sRadius + otherSRadius);

    } else if (collider->IsClassType(BoxCollider::Type)) {
        BoxCollider* otherBoxCollider = (BoxCollider*)collider;
        BoxCollider::AABB aabb = otherBoxCollider->getAABB();

        Transform& transform = getGameObject().getTransform();
        glm::vec3 spherePos  = transform.getWorldPosition() + _center;
        glm::vec3 sphereScale = transform.getScale();
        float sRadius = fmaxf(fmaxf(sphereScale.x, sphereScale.y), sphereScale.z) * _radius;

        float x = fmaxf(aabb.minVec.x, fminf(spherePos.x, aabb.maxVec.x));
        float y = fmaxf(aabb.minVec.y, fminf(spherePos.y, aabb.maxVec.y));
        float z = fmaxf(aabb.minVec.z, fminf(spherePos.z, aabb.maxVec.z));

        // this is the same as isPointInsideSphere
        float distance = sqrtf((x - spherePos.x) * (x - spherePos.x) +
                                 (y - spherePos.y) * (y - spherePos.y) +
                                 (z - spherePos.z) * (z - spherePos.z));

        return distance < sRadius;
    }

    return false;
};