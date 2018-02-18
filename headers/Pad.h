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

    virtual void update(const float deltaTime);

    void setMinX(float minX);
    float getMinX();
    void setMaxX(float maxX);
    float getMaxX();

    void setVelocityX(float vX);
    float getVelocityX();

private:
    float _minX, _maxX = 0;
    float _velocityX = 0;
};

#endif //GAMEENGINE_PAD_H
