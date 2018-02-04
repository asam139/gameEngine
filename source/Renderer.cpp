//
// Created by Saul Moreno Abril on 02/02/2018.
//

#include "Renderer.h"

CLASS_DEFINITION(Component, Renderer)

Renderer::Renderer( std::string && initialValue) : Component( std::move( initialValue ) ) {

}

Renderer::~Renderer() {
    // Delete VAO
    glDeleteVertexArrays(1, &_VAO);
}

void Renderer::createVertexData(float *vertices, uint32_t vSize, uint32_t *indices, uint32_t iSize){
    uint32_t VAO;
    uint32_t VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    _indicesSize = iSize;
    _VAO = VAO;

}

void Renderer::createVertexData(float *vertices, uint32_t vSize, float *uv, uint32_t uvSize, float *normal,
                                uint32_t nSize, uint32_t *indices, uint32_t iSize) {
    uint32_t VAO;
    uint32_t vVBO, uvVBO, nVBO, EBO;
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &vVBO);
    glGenBuffers(1, &uvVBO);
    glGenBuffers(1, &nVBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vVBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, uvSize * sizeof(GLfloat), uv, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2,  GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, nVBO);
    glBufferData(GL_ARRAY_BUFFER, nSize * sizeof(GLfloat), normal, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3,  GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indices, GL_STATIC_DRAW);


    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vVBO);
    glGenBuffers(1, &uvVBO);
    glGenBuffers(1, &nVBO);
    glGenBuffers(1, &EBO);

    _indicesSize = iSize;
    _VAO = VAO;
}

void Renderer::setMaterial(std::shared_ptr<Material> material) {
    _material = std::move(material);
}

Material* Renderer::getMaterial() {
    return _material.get();
}


void Renderer::render() {
    if (_material) {
        _material->configureShader();
    }

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indicesSize, GL_UNSIGNED_INT, nullptr);
}



