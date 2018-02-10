//
// Created by Saul Moreno Abril on 27/01/2018.
//

#ifndef GAMEENGINE_SPHERE_H
#define GAMEENGINE_SPHERE_H

#include "GameObject.h"

class Sphere: public GameObject {
public:
    Sphere();
    Sphere(const glm::vec3 center, const float radius);
    ~Sphere() override;


    void update(const float deltaTime) override;

protected:
    glm::vec3 _center;
    float _radius;

    void configuration() override;

    void generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius);
};

#endif //GAMEENGINE_SPHERE_H
