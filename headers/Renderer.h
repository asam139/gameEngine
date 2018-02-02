//
// Created by Saul Moreno Abril on 02/02/2018.
//

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer {
public:
    Renderer(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize);
    Renderer(float* vertices, uint32_t vSize, float *uv, uint32_t uvSize, float *normal, uint32_t nSize, uint32_t *indices, uint32_t iSize);
    ~Renderer();

    void render();

protected:
    uint32_t _indicesSize = 0;
    uint32_t _VAO = 0;

    void createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize);
    void createVertexData(float* vertices, uint32_t vSize, float *uv, uint32_t uvSize, float *normal, uint32_t nSize, uint32_t *indices, uint32_t iSize);

private:
    Renderer(){};
};


#endif //GAMEENGINE_RENDERER_H
