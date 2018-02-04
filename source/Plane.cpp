//
// Created by Saul Moreno Abril on 22/01/2018.
//

#include "Plane.h"

const unsigned int _verticesMapSize = 32;
static float _verticesMap[] = {
        // Position             // UVs         // Normals
        -1.0f, 0.0f, 1.0f,      0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,       1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, -1.0f,      1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,     0.0f, 1.0f,    0.0f, 1.0f, 0.0f
};

const unsigned int _indecesMapSize = 6;
static unsigned int _indecesMap[] = {
        0, 1, 2,
        0, 2, 3
};


Plane::Plane() {
    configuration();
}

Plane::~Plane() {

}

void Plane::configuration() {
    AddComponent<Renderer>("Renderer", this);
    Renderer& renderer =  GetComponent<Renderer>();
    renderer.createVertexData(_verticesMap, _verticesMapSize, _indecesMap, _indecesMapSize);
}

void Plane::update(const float deltaTime) {


}