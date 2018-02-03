//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Renderer.h"

typedef struct {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
} Transform;


class GameObject {
public:
    GameObject();
    virtual ~GameObject();

    virtual void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    virtual void setRotation(glm::vec3 rotation);
    glm::vec3 getRotation();
    virtual void setScale(glm::vec3 scale);
    glm::vec3 getScale();

    glm::mat4 getModel();

    virtual void update(const float deltaTime);
    virtual void display(glm::mat4 projection, glm::mat4 view, glm::vec3 cameraPos);

    Renderer* getRenderer();

protected:
    Transform _transform;

    virtual void configuration();


    std::shared_ptr<Renderer> _renderer;
};


#endif //GAMEENGINE_GAMEOBJECT_H
