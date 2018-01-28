//
// Created by Saul Moreno Abril on 28/01/2018.
//

#include <GameObject.h>
#include "Light.h"


Light::Light(Shader* shader) {
    _shader = shader;

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

Shader* Light::getShader() {
    return _shader;
}

void Light::configureShader() {
    _shader->set("light.position", _transform.position);

    _shader->set("light.ambient", _ambientColor);
    _shader->set("light.diffuse", _diffuseColor);
    _shader->set("light.specular", _specularColor);
}