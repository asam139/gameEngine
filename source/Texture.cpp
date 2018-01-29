//
// Created by Saul Moreno Abril on 29/01/2018.
//

#include "Texture.h"

#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

Texture::Texture(const char *path, GLenum type) {
    ///////////////////////////
    // Configure stb
    // It is not better place to do this
    stbi_set_flip_vertically_on_load(true);
    ///////////////////////////

    uint32_t texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint width, height, nChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        std::cout << "Failed To Load Texture" << path << std::endl;
        assert(0);
    }
    _texture = texture;
}

Texture::~Texture() {
    glDeleteTextures(1, &_texture);
}

uint32_t Texture::getTexture() const {
    return _texture;
}

