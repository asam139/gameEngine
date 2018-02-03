//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_CUBE_H
#define GAMEENGINE_CUBE_H

#include "GameObject.h"

class Cube: public GameObject {
public:
    Cube();
    Cube(const glm::vec3 center, float radius);
    ~Cube() override;


    void update(const float deltaTime) override;

protected:
    glm::vec3 _center;
    float _radius;

    void configuration() override;
};


#endif //GAMEENGINE_CUBE_H
