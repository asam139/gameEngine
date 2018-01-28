//
// Created by Saul Moreno Abril on 28/01/2018.
//

#include "Material.h"


Material::Material(Shader* shader) {
    _shader = shader;

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
    _shader->set("material.ambient_color", _ambientColor);
}

glm::vec3 Material::getAmbientColor() {
    return _ambientColor;
}

void Material::setDiffuseColor(glm::vec3 diffuseColor) {
    _diffuseColor = diffuseColor;
    _shader->set("material.diffuse_color", _diffuseColor);
}

glm::vec3 Material::getDiffuseColor() {
    return _diffuseColor;
}

void Material::setDiffuseText(uint32_t diffuseText) {
    _diffuseText = diffuseText;
    _shader->set("material.diffuse_text", _diffuseText);
}

uint32_t Material::getDiffuseText() {
    return _diffuseText;
}

void Material::setSpecularColor(glm::vec3 specularColor) {
    _specularColor = specularColor;
    _shader->set("material.specular_color", _specularColor);
}

glm::vec3 Material::getSpecularColor() {
    return _specularColor;
}

void Material::setSpecularText(uint32_t specularText) {
    _specularText = specularText;
    _shader->set("material.specular_text", _specularText);
}

uint32_t Material::getSpecularText() {
    return _specularText;
}

void Material::setShininess(float shininess) {
    _shininess = shininess;
    _shader->set("material.shininess", _shininess);
}

float Material::getShininess() {
    return _shininess;
}


Shader* Material::getShader() {
    return _shader;
}

void Material::configureShader() {
    _shader->set("material.ambient_color", _ambientColor);
    _shader->set("material.diffuse_color", _diffuseColor);
    _shader->set("material.diffuse_text", _diffuseText);
    _shader->set("material.specular_color", _specularColor);
    _shader->set("material.specular_text", _specularText);
    _shader->set("material.shininess", _shininess);
}