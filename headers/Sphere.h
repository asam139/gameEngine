//
// Created by Saul Moreno Abril on 27/01/2018.
//

#ifndef GAMEENGINE_SPHERE_H
#define GAMEENGINE_SPHERE_H

#include "GameObject.h"

class Sphere: public GameObject {
public:
    Sphere();
    Sphere(const glm::vec3 _center, const float radius);
    ~Sphere() override;


    void update(const float deltaTime) override;

protected:
    glm::vec3 _center;
    float _radius;

    void configuration() override;

    void generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius);

    uint32_t createVertexData(float* vertices, uint32_t vSize, float *uv, uint32_t uvSize, float *normal, uint32_t nSize, uint32_t* indices, uint32_t iSize);
};

#endif //GAMEENGINE_SPHERE_H
