//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_CUBE_H
#define GAMEENGINE_CUBE_H

#include "GameObject.h"

class Cube: public GameObject {
public:
    Cube();
    ~Cube();

protected:
    virtual void configuration();

    virtual uint32_t createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO);
};


#endif //GAMEENGINE_CUBE_H
