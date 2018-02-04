//
// Created by Saul Moreno Abril on 04/02/2018.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"


class Transform : public Component {
CLASS_DECLARATION(Transform)

public:
    Transform( std::string && initialValue, GameObject * owner);


    virtual void setPosition(glm::vec3 position);
    glm::vec3 getPosition() const;
    virtual void setRotation(glm::vec3 rotation);
    glm::vec3 getRotation() const;
    virtual void setScale(glm::vec3 scale);
    glm::vec3 getScale() const;

    glm::mat4 getModel() const;

    void setParentModel(glm::mat4 parentModel);
    glm::mat4 getParentModel();

    bool dirty;

protected:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _parentModel;
};


#endif //GAMEENGINE_TRANSFORM_H
