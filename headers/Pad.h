//
// Created by Saul Moreno Abril on 11/02/2018.
//

#ifndef GAMEENGINE_PAD_H
#define GAMEENGINE_PAD_H


#include "Cube.h"

class Pad : public Cube {
public:
    Pad();
    Pad(const glm::vec3 center, const float radius);
};

#endif //GAMEENGINE_PAD_H
