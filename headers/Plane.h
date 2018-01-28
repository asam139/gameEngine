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
    uint32_t _VBO, _EBO;

    void configuration() override;

    uint32_t createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO);
};

#endif //GAMEENGINE_PLANE_H
