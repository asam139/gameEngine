//
// Created by Saul Moreno Abril on 10/01/2018.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <glm.hpp>

#include <cstdint>
#include <string>


class  Shader {
    enum class Type {
        Vertex = 0,
        Fragment = 1,
        Geometry = 2,
        Program = 3
    };

    public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    ~Shader();

    void use() const;

    private:
        Shader() {};
        void checkError(const uint32_t shader, const Type type) const;
        void loadShader(const char* path, std::string* code);

        uint32_t id_;
};


#endif //GAMEENGINE_SHADER_H
