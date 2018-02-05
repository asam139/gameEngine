//
// Created by Saul Moreno Abril on 05/02/2018.
//

#ifndef GAMEENGINE_BOXCOLLIDER_H
#define GAMEENGINE_BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider {

CLASS_DECLARATION( BoxCollider )

public:
    BoxCollider( std::string && initialValue, GameObject *owner);

    void setSize(glm::vec3 size);
    glm::vec3 getSize();

protected:
    glm::vec3 _size;
};


#endif //GAMEENGINE_BOXCOLLIDER_H
