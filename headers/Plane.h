//
// Created by Saul Moreno Abril on 22/01/2018.
//

#ifndef GAMEENGINE_PLANE_H
#define GAMEENGINE_PLANE_H

#include "GameObject.h"

class Plane: public GameObject {
public:
    Plane();
    ~Plane() override;

    void update(const float deltaTime) override;

protected:
    void configuration() override;
};

#endif //GAMEENGINE_PLANE_H
