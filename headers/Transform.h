//
// Created by Saul Moreno Abril on 04/02/2018.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <glm/gtx/quaternion.hpp>

#include "Component.h"


class Transform : public Component {
CLASS_DECLARATION(Transform)

public:
    Transform( std::string && initialValue, GameObject * owner);


    virtual void setPosition(glm::vec3 position);
    glm::vec3 getPosition() const;


    virtual void setRotation(glm::quat rotation);
    void setRotation(glm::vec3 eulerAngles);
    void setRotation(float rotationAngle, glm::vec3 rotationAxis);
    glm::quat getRotation() const;
    virtual void setScale(glm::vec3 scale);
    glm::vec3 getScale() const;

    glm::mat4 getModel() const;

    void setParentModel(glm::mat4 parentModel);
    glm::mat4 getParentModel();

    bool dirty;

protected:
    glm::vec3 _position;
    glm::quat _rotation;
    glm::vec3 _scale;

    glm::mat4 _parentModel;
};


#endif //GAMEENGINE_TRANSFORM_H
