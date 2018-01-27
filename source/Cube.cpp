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
    // Delete VAO, VBO and EBO
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}

void Cube::configuration() {
    // Empty Object
    uint32_t verticesSize = _verticesMapSize;
    float* vertices = _verticesMap;
    _indicesSize = _indecesMapSize;
    _indices = _indecesMap;

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

    _VAO = createVertexData(vertices, verticesSize, _indices, _indicesSize,  &_VBO, &_EBO);
}

uint32_t Cube::createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO) {
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return VAO;
}


void Cube::update(const float deltaTime) {

}