//
// Created by Saul Moreno Abril on 28/01/2018.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Material {
public:
    Material(std::shared_ptr<Shader> shader);
    ~Material();

    void setAmbientColor(glm::vec3 ambientColor);
    glm::vec3 getAmbientColor();

    void setDiffuseColor(glm::vec3 diffuseColor);
    void setDiffuseTexture(std::shared_ptr<Texture> texture);
    void setDiffuseText(uint32_t diffuseText);
    glm::vec3 getDiffuseColor();
    Texture* getDiffuseTexture();
    uint32_t getDiffuseText();


    void setSpecularColor(glm::vec3 specularColor);
    void setSpecularTexture(std::shared_ptr<Texture> texture);
    void setSpecularText(uint32_t specularText);
    glm::vec3 getSpecularColor();
    Texture* getSpecularTexture();
    uint32_t getSpecularText();
    float getShininess();
    void setShininess(float shininess);


    void setEmissionActive(bool emissionActive);
    void setEmissiveColor(glm::vec3 emissiveColor);
    void setEmissiveTexture(std::shared_ptr<Texture> texture);
    void setEmissiveText(uint32_t emissiveText);
    bool getEmissionActive();
    glm::vec3 getEmissiveColor();
    Texture* getEmissiveTexture();
    uint32_t getEmissiveText();


    Shader* getShader();
    void configureShader();

protected:
    glm::vec3 _ambientColor;

    glm::vec3 _diffuseColor;
    std::shared_ptr<Texture> _diffuseTexture;
    uint32_t _diffuseText;

    glm::vec3 _specularColor;
    std::shared_ptr<Texture> _specularTexture;
    uint32_t _specularText;
    float _shininess;

    bool _emissionActive;
    glm::vec3 _emissiveColor;
    std::shared_ptr<Texture> _emissiveTexture;
    uint32_t _emissiveText;

    std::shared_ptr<Shader> _shader;
private:

};


#endif //GAMEENGINE_MATERIAL_H
