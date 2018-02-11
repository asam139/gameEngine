//
// Created by Saul Moreno Abril on 11/02/2018.
//

#ifndef GAMEENGINE_SPHERECOLLIDER_H
#define GAMEENGINE_SPHERECOLLIDER_H


#include "Collider.h"

class SphereCollider : public Collider {

CLASS_DECLARATION( SphereCollider )

public:
    SphereCollider( std::string && initialValue, GameObject *owner);

    void setRadius(float radius);
    float getRadius();

    virtual bool collision(Collider  *collider);

protected:
    float _radius;
};


#endif //GAMEENGINE_SPHERECOLLIDER_H
