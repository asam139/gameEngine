//
// Created by Saul Moreno Abril on 28/01/2018.
//

#include "Material.h"


Material::Material(std::shared_ptr<Shader> shader) {
    _shader = shader;
    _diffuseTexture = nullptr;
    _specularTexture = nullptr;

    setAmbientColor(glm::vec3(0.5f));
    setDiffuseColor(glm::vec3(1.0f));
    setDiffuseText(0);
    setSpecularColor(glm::vec3(0.25f));
    setSpecularText(0);
    setShininess(32.f);
}

Material::~Material() {

}


void Material::setAmbientColor(glm::vec3 ambientColor) {
    _ambientColor = ambientColor;
}

glm::vec3 Material::getAmbientColor() {
    return _ambientColor;
}

void Material::setDiffuseColor(glm::vec3 diffuseColor) {
    _diffuseColor = diffuseColor;
}

glm::vec3 Material::getDiffuseColor() {
    return _diffuseColor;
}

void Material::setDiffuseTexture(std::shared_ptr<Texture> texture) {
    _diffuseTexture = texture;
}

Texture* Material::getDiffuseTexture() {
    return _diffuseTexture.get();
}

void Material::setDiffuseText(uint32_t diffuseText) {
    _diffuseText = diffuseText;
}

uint32_t Material::getDiffuseText() {
    return _diffuseText;
}

void Material::setSpecularColor(glm::vec3 specularColor) {
    _specularColor = specularColor;
}

glm::vec3 Material::getSpecularColor() {
    return _specularColor;
}

void Material::setSpecularTexture(std::shared_ptr<Texture> texture) {
    _specularTexture = texture;
}

Texture* Material::getSpecularTexture() {
    return _specularTexture.get();
}


void Material::setSpecularText(uint32_t specularText) {
    _specularText = specularText;
}

uint32_t Material::getSpecularText() {
    return _specularText;
}

void Material::setShininess(float shininess) {
    _shininess = shininess;
}

float Material::getShininess() {
    return _shininess;
}


Shader* Material::getShader() {
    return _shader.get();
}

void Material::configureShader() {
    _shader->set("material.ambient_color", _ambientColor);

    _shader->set("material.diffuse_color", _diffuseColor);
    if (_diffuseTexture != nullptr) {
        setDiffuseText(0);
        _diffuseTexture->activeTextureAs(GL_TEXTURE0);
    }
    _shader->set("material.diffuse_text", _diffuseText);

    _shader->set("material.specular_color", _specularColor);
    if (_specularTexture != nullptr) {
        setDiffuseText(1);
        _specularTexture->activeTextureAs(GL_TEXTURE1);
    }
    _shader->set("material.specular_text", _specularText);

    _shader->set("material.shininess", _shininess);

    // Set to use
    _shader->use();
}