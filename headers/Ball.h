//
// Created by Saul Moreno Abril on 10/02/2018.
//

#ifndef GAMEENGINE_BALL_H
#define GAMEENGINE_BALL_H

#include "Sphere.h"

class Ball : public Sphere {
public:
    Ball();
    Ball(const glm::vec3 center, const float radius);
};


#endif //GAMEENGINE_BALL_H
