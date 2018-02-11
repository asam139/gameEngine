//
// Created by Saul Moreno Abril on 05/02/2018.
//

#ifndef GAMEENGINE_COLLIDER_H
#define GAMEENGINE_COLLIDER_H

#include "Component.h"

#include <glm/glm.hpp>

class Collider : public Component {

    CLASS_DECLARATION( Collider )

public:
    Collider(  std::string && initialValue, GameObject * owner );

    void setCenter(glm::vec3 center);
    glm::vec3 getCenter();

    virtual bool collision(Collider  *collider) = 0;

protected:
    glm::vec3 _center;
};


#endif //GAMEENGINE_COLLIDER_H
