//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>


class GameObject {
public:
    GameObject() noexcept = default; //Empty Constructor
    virtual ~GameObject() noexcept = default; //Destructor

    uint32_t getVAO() const;
    uint32_t getIndecesSize() const;

protected:
    uint32_t _verticesSize = 0;
    float* _vertices = nullptr;

    uint32_t _indicesSize = 0;
    unsigned int* _indices = nullptr;

    virtual void configuration() = 0;

    unsigned int _VBO = 0, _EBO = 0, _VAO = 0;
    virtual uint32_t createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO) = 0;
};


#endif //GAMEENGINE_GAMEOBJECT_H
