//
// Created by Saul Moreno Abril on 10/02/2018.
//

#ifndef GAMEENGINE_TOOLS_H
#define GAMEENGINE_TOOLS_H

#include <glad/glad.h>
#include "Shader.h"

unsigned int makeBuffer(void *data, int vertexCount, int vertexsize);
void assignVBOtoAttribute(Shader *shader, char* attributeName, GLuint bufVBO, int vertexsize);

#endif //GAMEENGINE_TOOLS_H
