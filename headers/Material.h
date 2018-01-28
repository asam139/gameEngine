//
// Created by Saul Moreno Abril on 28/01/2018.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include <glm/glm.hpp>
#include "shader.h"

class Material {
public:
    Material(Shader *shader);
    ~Material();

    void setAmbientColor(glm::vec3 ambientColor);
    void setDiffuseColor(glm::vec3 diffuseColor);
    void setDiffuseText(uint32_t diffuseText);
    void setSpecularColor(glm::vec3 specularColor);
    void setSpecularText(uint32_t specularText);
    void setShininess(float shininess);

    glm::vec3 getAmbientColor();
    glm::vec3 getDiffuseColor();
    uint32_t getDiffuseText();
    glm::vec3 getSpecularColor();
    uint32_t getSpecularText();
    float getShininess();

    Shader* getShader();
    void configureShader();

protected:
    Shader* _shader;

    glm::vec3 _ambientColor;
    glm::vec3 _diffuseColor;
    uint32_t _diffuseText;
    glm::vec3 _specularColor;
    uint32_t _specularText;
    float _shininess;

private:

};


#endif //GAMEENGINE_MATERIAL_H
