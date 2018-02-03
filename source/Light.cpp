//
// Created by Saul Moreno Abril on 28/01/2018.
//

#include "Light.h"


Light::Light() {
    setAmbientColor(glm::vec3(0.5f));
    setDiffuseColor(glm::vec3(1.0f));
    setSpecularColor(glm::vec3(0.25f));
}

Light::~Light() {

}

void Light::setAmbientColor(glm::vec3 ambientColor) {
    _ambientColor = ambientColor;
}

glm::vec3 Light::getAmbientColor() {
    return _ambientColor;
}

void Light::setDiffuseColor(glm::vec3 diffuseColor) {
    _diffuseColor = diffuseColor;
}

glm::vec3 Light::getDiffuseColor() {
    return _diffuseColor;
}

void Light::setSpecularColor(glm::vec3 specularColor) {
    _specularColor = specularColor;
}

glm::vec3 Light::getSpecularColor() {
    return _specularColor;
}


void Light::configureShader(Shader *shader) {
    shader->set("light.position", _transform.position);

    shader->set("light.ambient", _ambientColor);
    shader->set("light.diffuse", _diffuseColor);
    shader->set("light.specular", _specularColor);
}