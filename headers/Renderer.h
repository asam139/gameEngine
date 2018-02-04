//
// Created by Saul Moreno Abril on 02/02/2018.
//

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Component.h"
#include "Material.h"


class Renderer : public Component {
CLASS_DECLARATION( Renderer )

public:
    Renderer( std::string && initialValue);
    ~Renderer() override;

    void createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize);
    void createVertexData(float* vertices, uint32_t vSize, float *uv, uint32_t uvSize, float *normal, uint32_t nSize, uint32_t *indices, uint32_t iSize);

    void setMaterial(std::shared_ptr<Material> material);
    Material* getMaterial();

    void render();

protected:
    uint32_t _indicesSize = 0;
    uint32_t _VAO = 0;



    std::shared_ptr<Material> _material = nullptr;

private:

};


#endif //GAMEENGINE_RENDERER_H
