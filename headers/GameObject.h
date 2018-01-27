//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>


class GameObject {
public:
    virtual ~GameObject() {};
    virtual void update(const float deltaTime) = 0;

    uint32_t getVAO() const;
    uint32_t getIndecesSize() const;
protected:
    GameObject() {};

    uint32_t _indicesSize = 0;
    uint32_t* _indices = nullptr;

    virtual void configuration() = 0;

    unsigned int _VBO = 0, _EBO = 0, _VAO = 0;
};


#endif //GAMEENGINE_GAMEOBJECT_H
