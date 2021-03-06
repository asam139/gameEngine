//
// Created by Saul Moreno Abril on 28/01/2018.
//

#include "Material.h"


Material::Material(std::shared_ptr<Shader> shader) {
    _shader = shader;

    // Ambient
    setAmbientColor(glm::vec3(0.5f));

    // Diffuse
    setDiffuseColor(glm::vec3(1.0f));
    _diffuseTexture = nullptr;

    // Specular
    setSpecularColor(glm::vec3(0.25f));
    _specularTexture = nullptr;
    setShininess(32.f);

    // Emissive
    setEmissiveColor(glm::vec3(0.0f));
    _emissiveTexture = nullptr;
}

Material::~Material() {

}

// Ambient
void Material::setAmbientColor(glm::vec3 ambientColor) {
    _ambientColor = ambientColor;
}

glm::vec3 Material::getAmbientColor() {
    return _ambientColor;
}


// Diffuse
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

// Specular
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

void Material::setShininess(float shininess) {
    _shininess = shininess;
}

float Material::getShininess() {
    return _shininess;
}

// Emissive

void Material::setEmissiveColor(glm::vec3 emissiveColor) {
    _emissiveColor = emissiveColor;
}

glm::vec3 Material::getEmissiveColor() {
    return _emissiveColor;
}

void Material::setEmissiveTexture(std::shared_ptr<Texture> texture) {
    _emissiveTexture = texture;
}

Texture* Material::getEmissiveTexture() {
    return _emissiveTexture.get();
}

void Material::setEmissionActive(bool emissionActive) {
    _emissionActive = emissionActive;
}

bool Material::getEmissionActive() {
    return _emissionActive;
}

// Shader
Shader* Material::getShader() {
    return _shader.get();
}

void Material::configureShader() {
    // Ambient
    _shader->set("material.ambient_color", _ambientColor);

    // Diffuse
    _shader->set("material.diffuse_color", _diffuseColor);
    if (_diffuseTexture != nullptr) {
        _diffuseTexture->activeTextureAs(GL_TEXTURE0);
        _shader->set("material.specular_text", 1);
    }

    // Specular
    _shader->set("material.specular_color", _specularColor);
    if (_specularTexture != nullptr) {
        _specularTexture->activeTextureAs(GL_TEXTURE1);
        _shader->set("material.specular_text", 1);
    }

    _shader->set("material.shininess", _shininess);

    // Emissive
    _shader->set("material.emission_active", _emissionActive);
    if (_emissionActive) {
        _shader->set("material.emissive_color", _emissiveColor);
        if (_emissiveTexture != nullptr) {
            _emissiveTexture->activeTextureAs(GL_TEXTURE2);
            _shader->set("material.emissive_text", 2);
        }
    }

    // Set to use
    _shader->use();
}