//
// Created by Saul Moreno Abril on 28/01/2018.
//

#ifndef GAMEENGINE_LIGHT_H
#define GAMEENGINE_LIGHT_H

#include "shader.h"

class Light {
public:
    Light();
    ~Light();

    void setAmbientColor(glm::vec3 ambientColor);
    void setDiffuseColor(glm::vec3 diffuseColor);
    void setSpecularColor(glm::vec3 specularColor);

    glm::vec3 getAmbientColor();
    glm::vec3 getDiffuseColor();
    glm::vec3 getSpecularColor();

    void configureShader(Shader *shader);

protected:
    glm::vec3 _ambientColor;
    glm::vec3 _diffuseColor;
    glm::vec3 _specularColor;


private:

};


#endif //GAMEENGINE_LIGHT_H
