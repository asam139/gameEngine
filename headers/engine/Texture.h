//
// Created by Saul Moreno Abril on 29/01/2018.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <glad/glad.h>

class Texture {



public:
    Texture(const char *path, GLenum type, bool flip);
    Texture(const char* path, GLenum type);
    ~Texture();

    uint32_t getTexture() const;
    void activeTextureAs(GLenum texture) const;

protected:
    uint32_t _texture;


private:

};


#endif //GAMEENGINE_TEXTURE_H
