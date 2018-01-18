//
// Created by Saul Moreno Abril on 17/01/2018.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class GameObject {
public:
    GameObject(); //Empty Constructor
    virtual ~GameObject(); //Destructor

    //Constructor with Vectors
    /*Camera(const glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           const float yaw = kYaw, const float pitch = kPitch);*/

    //Constructor with Scalars


    //Returns current view matrix
    //glm::mat4 getViewMatrix() const;

    uint32_t getVAO() const;
    int getIndecesSize() const;

protected:
    int _verticesSize;
    float* _vertices;

    int _indicesSize;
    unsigned int* _indices;

    virtual void configuration() = 0;

    unsigned int _VBO, _EBO, _VAO;
    virtual uint32_t createVertexData(float* vertices, uint32_t vSize, uint32_t* indices, uint32_t iSize,  uint32_t* VBO, uint32_t* EBO) = 0;

};


#endif //GAMEENGINE_GAMEOBJECT_H
