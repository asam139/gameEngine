//
// Created by Saul Moreno Abril on 17/01/2018.
//

#include "Cube.h"


#include <iostream>

Cube::Cube() {
    configuration();
}

Cube::~Cube() {
    // Delete VAO, VBO and EBO
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}

void Cube::configuration() {
    // Empty Object
    _verticesSize = 120;
    _vertices = (float[120]){
            // Position             // UVs
            -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, //Front
            0.5f, -0.5f, 0.5f,      1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,       1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,      0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,      0.0f, 0.0f, //Right
            0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f,
            0.5f, 0.5f, 0.5f,       0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, //Back
            -0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
            0.5f, 0.5f, -0.5f,      0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, //Left
            -0.5f, 0.5f, 0.5f,      1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     0.0f, 1.0f, //Bottom
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,      1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, //Top
            0.5f, 0.5f, 0.5f,       1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f

    };
    _indicesSize = 36;
    _indices = (unsigned int[36]){
            0, 1, 2,        0, 2, 3, //Front
            4, 5, 6,        4, 6, 7, //Right
            8, 9, 10,       8, 10, 11, //Back
            12, 13, 14,     12, 14, 15, //Left
            16, 17, 18,     16, 18, 19, //Bottom
            20, 21, 22,     20, 22, 23 //Top
    };

    _VAO = createVertexData(_vertices, _verticesSize, _indices, _indicesSize,  &_VBO, &_EBO);
}

uint32_t Cube::generatedVertices(float* vertices) {

    _vertices = (float[72]){};
    int index = 0;

    // Back & Front
    for (int j = 0; j < 4; ++j) {
        const int x = j & 1;
        const int y = (j>>1) & 1;
        const int z = (j>>2) & 1;

        _vertices[index + j] = x;
        _vertices[index + j] = y;
        _vertices[index + j] = z;

        _vertices[index + j + 4] = x;
        _vertices[index + j + 4] = y;
        _vertices[index + j + 4] = z - 1;
    }

    index = 24;
    // Right & Left
    for (int j = 1; j < 8; j = j + 2) {
        const int x = j & 1;
        const int y = (j>>1) & 1;
        const int z = (j>>2) & 1;

        _vertices[index + j] = x;
        _vertices[index + j] = y;
        _vertices[index + j] = z;

        _vertices[index + j + 4] = x - 1;
        _vertices[index + j + 4] = y;
        _vertices[index + j + 4] = z;
    }

    // Up & Down
    for (int j = 2; j < 4; j++) {
        const int x = j & 1;
        const int y = (j>>1) & 1;
        const int z = (j>>2) & 1;

        const int x2 = (j+4) & 1;
        const int y2 = ((j+4)>>1) & 1;
        const int z2 = ((j+4)>>2) & 1;

        _vertices[index + j] = x;
        _vertices[index + j] = y;
        _vertices[index + j] = z;

        _vertices[index + j + 2] = x2;
        _vertices[index + j + 2] = y2;
        _vertices[index + j + 2] = z2;

        _vertices[index + j + 4] = x;
        _vertices[index + j + 4] = y;
        _vertices[index + j + 4] = z;

        _vertices[index + j + 4 + 2] = x2;
        _vertices[index + j + 4 + 2] = y2 - 1;
        _vertices[index + j + 4 + 2] = z2;
    }

    index = 48;
    return 0;
}


uint32_t Cube::createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO) {
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2,  GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}