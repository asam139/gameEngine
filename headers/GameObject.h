//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

typedef struct {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
} Transform;


class GameObject {
public:
    GameObject();
    virtual ~GameObject();

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    void setRotation(glm::vec3 rotation);
    glm::vec3 getRotation();
    void setScale(glm::vec3 scale);
    glm::vec3 getScale();

    glm::mat4 getModel();

    virtual void update(const float deltaTime);

    uint32_t getVAO() const;
    uint32_t getIndecesSize() const;

protected:
    Transform _transform;

    virtual void configuration();

    uint32_t _indicesSize = 0;
    uint32_t* _indices = nullptr;

    uint32_t _VAO = 0;
};


#endif //GAMEENGINE_GAMEOBJECT_H
