//
// Created by Saul Moreno Abril on 28/01/2018.
//

#include "Light.h"

CLASS_DEFINITION(Component, Light)

Light::Light( std::string && initialValue ) : Component( std::move( initialValue ) ) {
    setAmbientColor(glm::vec3(0.5f));
    setDiffuseColor(glm::vec3(1.0f));
    setSpecularColor(glm::vec3(0.25f));
}

void Light::setAmbientColor(glm::vec3 ambientColor) {
    _ambientColor = ambientColor;
}

glm::vec3 Light::getAmbientColor() const {
    return _ambientColor;
}

void Light::setDiffuseColor(glm::vec3 diffuseColor) {
    _diffuseColor = diffuseColor;
}

glm::vec3 Light::getDiffuseColor() const {
    return _diffuseColor;
}

void Light::setSpecularColor(glm::vec3 specularColor) {
    _specularColor = specularColor;
}

glm::vec3 Light::getSpecularColor() const {
    return _specularColor;
}
