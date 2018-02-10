//
// Created by Saul Moreno Abril on 17/01/2018.
//

#include "Cube.h"

const unsigned int _verticesMapSize = 192;
static float _verticesMap[] = {
    // Position             // UVs              // Normals
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,         0.0f, 0.0f, 1.0f,   //Front
    0.5f, -0.5f, 0.5f,      1.0f, 0.0f,         0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 1.0f,         0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f,         0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,      0.0f, 0.0f,         1.0f, 0.0f, 0.0f,   //Right
    0.5f, -0.5f, -0.5f,     1.0f, 0.0f,         1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,      1.0f, 1.0f,         1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,       0.0f, 1.0f,         1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,         0.0f, 0.0f, -1.0f,  //Back
    -0.5f, 0.5f, -0.5f,     1.0f, 1.0f,         0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,      0.0f, 1.0f,         0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,     0.0f, 0.0f,         0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, 0.5f,     1.0f, 0.0f,         -1.0f, 0.0f, 0.0f,  //Left
    -0.5f, 0.5f, 0.5f,      1.0f, 1.0f,         -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,         -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,         -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 1.0f,         0.0f, -1.0f, 0.0f,  //Bottom
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,         0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,     1.0f, 0.0f,         0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,      1.0f, 1.0f,         0.0f, -1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 0.0f,         0.0f, 1.0f, 0.0f,   //Top
    0.5f, 0.5f, 0.5f,       1.0f, 0.0f,         0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f,      1.0f, 1.0f,         0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,          0.0f, 1.0f, 0.0f
};


const unsigned int _indecesMapSize = 36;
static unsigned int _indecesMap[] = {
    0, 1, 2,        0, 2, 3, //Front
    4, 5, 6,        4, 6, 7, //Right
    8, 9, 10,       8, 10, 11, //Back
    12, 13, 14,     12, 14, 15, //Left
    16, 17, 18,     16, 18, 19, //Bottom
    20, 21, 22,     20, 22, 23 //Top
};


const unsigned int _numberOfVertices = 24;


Cube::Cube() {
    _center = glm::vec3(0.f, 0.f, 0.f);
    _radius = 1.f;

    configuration();
}

Cube::Cube(const glm::vec3 center, float radius) {
    _center = center;
    _radius = radius;

    configuration();
}

Cube::~Cube() {
}

void Cube::configuration() {
    float* vertices = _verticesMap;
    for (int i = 0; i < _numberOfVertices; i++) {
        int offset = i*8;
        vertices[offset] = (vertices[offset] - _center.x) * _radius;
        offset++;
        vertices[offset] = (vertices[offset] - _center.y) * _radius;
        offset++;
        vertices[offset] = (vertices[offset] - _center.z) * _radius;
        offset++;
        vertices[offset] = vertices[offset];
        offset++;
        vertices[offset] = vertices[offset];
        offset++;
        vertices[offset] = vertices[offset];
        offset++;
        vertices[offset] = vertices[offset];
        offset++;
        vertices[offset] = vertices[offset];
    }

    AddComponent<Renderer>("Renderer", this);
    Renderer* renderer =  GetComponent<Renderer>();
    renderer->createVertexData(vertices, _verticesMapSize, _indecesMap, _indecesMapSize);
}

void Cube::update(const float deltaTime) {

}