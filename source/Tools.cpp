//
// Created by Saul Moreno Abril on 10/02/2018.
//

#include "Tools.h"

unsigned int makeBuffer(void *data, int vertexCount, int vertexsize) {
    unsigned int handle;
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexsize, data, GL_STATIC_DRAW);

    return handle;
}

void assignVBOtoAttribute(Shader *shader, char* attributeName, GLuint bufVBO, int vertexsize) {
    unsigned int location = shader->getAttribLocation(attributeName);
    glBindBuffer(GL_ARRAY_BUFFER,bufVBO);
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, vertexsize, GL_FLOAT, GL_FALSE, 0, NULL);
}