//
// Created by Saul Moreno Abril on 27/01/2018.
//

#include "Sphere.h"

Sphere::Sphere() {
    _center = glm::vec3(0.f, 0.f, 0.f);
    _radius = 1.f;
    configuration();
}

Sphere::Sphere(const glm::vec3 center, const float radius) {
    _center = center;
    _radius = radius;
    configuration();
}

Sphere::~Sphere() {
    // Delete VAO
    glDeleteVertexArrays(1, &_VAO);
}

void Sphere::configuration() {
    constexpr uint32_t slices = 25;
    constexpr uint32_t stacks = 25;

    constexpr uint32_t nVerts = (slices + 1) * (stacks + 1);
    constexpr uint32_t elements = (slices * 2 * (stacks - 1)) * 3;

    uint32_t verticesSize = 3 * nVerts;
    float vertices[verticesSize];

    uint32_t uvSize = 2 * nVerts;
    float uv[uvSize];

    uint32_t normalSize = 3 * nVerts;
    float normal[normalSize];

    uint32_t indicesSize = elements;
    uint32_t indices[indicesSize];

    generateVerts(vertices, normal, uv, indices, slices, stacks, _radius);

    _indicesSize = indicesSize;
    _indices = indices;
    _VAO = createVertexData(vertices, verticesSize, uv, uvSize, normal, normalSize, indices, indicesSize);
}


void Sphere::generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius) {
    float theta, phi;       // Generate positions and normals
    float thetaFac = (float)((2.0 * M_PI) / slices);
    float phiFac = (float)(M_PI / stacks);
    float nx, ny, nz, s, t;
    uint32_t idx = 0, tIdx = 0;
    for (uint8_t i = 0; i <= slices; i++) {
        theta = i * thetaFac;
        s = (float)i / slices;
        for (uint8_t j = 0; j <= stacks; j++) {
            phi = j * phiFac;
            t = (float)j / stacks;
            nx = sinf(phi) * cosf(theta);
            ny = sinf(phi) * sinf(theta);
            nz = cosf(phi);
            verts[idx] = radius * (nx - _center.x);
            verts[idx + 1] = radius * (ny - _center.y);
            verts[idx + 2] = radius * (nz - _center.z);
            norms[idx] = nx;
            norms[idx + 1] = ny;
            norms[idx + 2] = nz;
            idx += 3;

            tex[tIdx] = s;
            tex[tIdx + 1] = t;
            tIdx += 2;
        }
    }

    idx = 0;                      // Generate the element list
    for (uint8_t i = 0; i < slices; i++) {
        uint32_t stackStart = i * (stacks + 1);
        uint32_t nextStackStart = (i + 1) * (stacks + 1);
        for (uint8_t j = 0; j < stacks; j++) {
            if (j == 0) {
                el[idx] = stackStart;
                el[idx + 1] = stackStart + 1;
                el[idx + 2] = nextStackStart + 1;
                idx += 3;
            }
            else if (j == stacks - 1) {
                el[idx] = stackStart + j;
                el[idx + 1] = stackStart + j + 1;
                el[idx + 2] = nextStackStart + j;
                idx += 3;
            }
            else {
                el[idx] = stackStart + j;
                el[idx + 1] = stackStart + j + 1;
                el[idx + 2] = nextStackStart + j + 1;
                el[idx + 3] = nextStackStart + j;
                el[idx + 4] = stackStart + j;
                el[idx + 5] = nextStackStart + j + 1;
                idx += 6;
            }
        }
    }
}



uint32_t Sphere::createVertexData(float* vertices, uint32_t vSize, float *uv, uint32_t uvSize, float *normal, uint32_t nSize, uint32_t *indices, uint32_t iSize) {
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

    return VAO;
}


void Sphere::update(const float deltaTime) {

}