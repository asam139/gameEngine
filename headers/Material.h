//
// Created by Saul Moreno Abril on 28/01/2018.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include <glm/glm.hpp>
#include "shader.h"
#include "Texture.h"

class Material {
public:
    Material(Shader *shader);
    ~Material();

    void setAmbientColor(glm::vec3 ambientColor);
    void setDiffuseColor(glm::vec3 diffuseColor);
    void setDiffuseTexture(Texture* texture);
    void setDiffuseText(uint32_t diffuseText);
    void setSpecularColor(glm::vec3 specularColor);
    void setSpecularTexture(Texture* texture);
    void setSpecularText(uint32_t specularText);
    void setShininess(float shininess);

    glm::vec3 getAmbientColor();
    glm::vec3 getDiffuseColor();
    Texture* getDiffuseTexture();
    uint32_t getDiffuseText();

    glm::vec3 getSpecularColor();
    Texture* getSpecularTexture();
    uint32_t getSpecularText();
    float getShininess();

    Shader* getShader();
    void configureShader();

protected:
    glm::vec3 _ambientColor;
    glm::vec3 _diffuseColor;

    Texture* _diffuseTexture;
    uint32_t _diffuseText;
    glm::vec3 _specularColor;
    Texture* _specularTexture;
    uint32_t _specularText;
    float _shininess;

    Shader* _shader;

private:

};


#endif //GAMEENGINE_MATERIAL_H
