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
    uint32_t _verticesSize;
    float* _vertices;

    uint32_t _indicesSize;
    unsigned int* _indices;

    virtual void configuration() = 0;

    unsigned int _VBO, _EBO, _VAO;
    virtual uint32_t createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO) = 0;
};


#endif //GAMEENGINE_GAMEOBJECT_H
