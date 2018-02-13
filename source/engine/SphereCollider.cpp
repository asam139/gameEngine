//
// Created by Saul Moreno Abril on 11/02/2018.
//

#include <engine/BoxCollider.h>
#include <engine/SphereCollider.h>
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
        SphereCollider::SSSS o_ssss = otherCollider->getSSSS();
        SphereCollider::SSSS ssss = getSSSS();

        float distance = sqrtf((ssss.pos.x - o_ssss.pos.x) * (ssss.pos.x - o_ssss.pos.x) +
                                 (ssss.pos.y - o_ssss.pos.y) * (ssss.pos.y - o_ssss.pos.y) +
                                 (ssss.pos.z - o_ssss.pos.z) * (ssss.pos.z - o_ssss.pos.z));
        return distance < (ssss.radius + o_ssss.radius);

    } else if (collider->IsClassType(BoxCollider::Type)) {
        BoxCollider* otherBoxCollider = (BoxCollider*)collider;
        BoxCollider::AABB aabb = otherBoxCollider->getAABB();

        SphereCollider::SSSS ssss = getSSSS();

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

SphereCollider::SSSS SphereCollider::getSSSS() {
    Transform& transform = getGameObject().getTransform();
    glm::vec3 spherePos  = transform.getWorldPosition() + _center;
    glm::vec3 sphereScale = transform.getScale();
    float sRadius = fmaxf(fmaxf(sphereScale.x, sphereScale.y), sphereScale.z) * _radius;

    SSSS ssss;
    ssss.pos = spherePos;
    ssss.radius = sRadius;

    return ssss;
}