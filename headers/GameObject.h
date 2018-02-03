//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Renderer.h"
#include "Light.h"

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
    glm::vec3 getPosition() const;
    virtual void setRotation(glm::vec3 rotation);
    glm::vec3 getRotation() const;
    virtual void setScale(glm::vec3 scale);
    glm::vec3 getScale() const;

    glm::mat4 getModel() const;

    virtual void update(const float deltaTime);
    virtual void display(const glm::mat4 projection, const glm::mat4 view, const glm::vec3 cameraPos, const glm::vec3 lightPos, const Light& light) const;

    void setRenderer(std::shared_ptr<Renderer> renderer);
    Renderer* getRenderer() const;

    void setLight(std::shared_ptr<Light> light);
    Light* getLight() const;

protected:
    Transform _transform;

    virtual void configuration();

    std::shared_ptr<Renderer> _renderer;
    std::shared_ptr<Light> _light;
};


#endif //GAMEENGINE_GAMEOBJECT_H
