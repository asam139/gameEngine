//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_CUBE_H
#define GAMEENGINE_CUBE_H

#include "GameObject.h"

class Cube: public GameObject {
public:
    Cube();
    ~Cube() override;

protected:
    void configuration() override;

    uint32_t createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO) override;
};


#endif //GAMEENGINE_CUBE_H
