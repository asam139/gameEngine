//
// Created by Saul Moreno Abril on 22/01/2018.
//

#include "Plane.h"

const unsigned int _verticesMapSize = 20;
static float _verticesMap[] = {
        // Position             // UVs
        -1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,       1.0f, 0.0f,
        1.0f, 0.0f, -1.0f,      1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,     0.0f, 1.0f
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
    // Delete VAO
    glDeleteVertexArrays(1, &_VAO);
}

void Plane::configuration() {
    // Empty Object
    uint32_t verticesSize = _verticesMapSize;
    float* vertices = _verticesMap;
    _indicesSize = _indecesMapSize;
    _indices = _indecesMap;

    _VAO = createVertexData(vertices, verticesSize, _indices, _indicesSize);
}

uint32_t Plane::createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize) {
    uint32_t VAO;
    uint32_t VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2,  GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return VAO;
}

void Plane::update(const float deltaTime) {


}