//
// Created by Saul Moreno Abril on 28/01/2018.
//

#ifndef GAMEENGINE_LIGHT_H
#define GAMEENGINE_LIGHT_H

#include <glm/glm.hpp>

#include "Component.h"

class Light : public Component {
CLASS_DECLARATION( Light )

public:
    Light( std::string && initialValue, GameObject * owner);

    void setAmbientColor(glm::vec3 ambientColor);
    void setDiffuseColor(glm::vec3 diffuseColor);
    void setSpecularColor(glm::vec3 specularColor);

    glm::vec3 getAmbientColor() const;
    glm::vec3 getDiffuseColor() const;
    glm::vec3 getSpecularColor() const;

protected:
    glm::vec3 _ambientColor;
    glm::vec3 _diffuseColor;
    glm::vec3 _specularColor;


private:

};


#endif //GAMEENGINE_LIGHT_H
