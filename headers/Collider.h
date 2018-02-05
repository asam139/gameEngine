//
// Created by Saul Moreno Abril on 05/02/2018.
//

#ifndef GAMEENGINE_COLLIDER_H
#define GAMEENGINE_COLLIDER_H

#include "Component.h"

class Collider : public Component {

    CLASS_DECLARATION( Collider )

public:

    Collider(  std::string && initialValue, GameObject * owner );
};


#endif //GAMEENGINE_COLLIDER_H
