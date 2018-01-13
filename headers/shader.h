//
// Created by Saul Moreno Abril on 10/01/2018.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <glad/glad.h>
#include <glm.hpp>

#include <cstdint>
#include <string>


class  Shader {
    public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    ~Shader();

    void use() const;

    void set(const char* name, const bool value) const;
    void set(const char* name, const GLint value) const;
    void set(const char* name, const GLuint value) const;
    void set(const char* name, const GLfloat value) const;
    void set(const char* name, const GLfloat value0, const GLfloat value1) const;
    void set(const char* name, const GLfloat value0, const GLfloat value1, const GLfloat value2) const;
    void set(const char* name, const GLfloat value0, const GLfloat value1, const GLfloat value2, const GLfloat value3) const;

    void set(const char* name, const glm::vec2& value) const;
    void set(const char* name, const glm::vec3& value) const;
    void set(const char* name, const glm::vec4& value) const;
    void set(const char* name, const glm::mat2& value) const;
    void set(const char* name, const glm::mat3& value) const;
    void set(const char* name, const glm::mat4& value) const;

    private:
        Shader() {};

        enum class Type {
            Vertex = 0,
            Fragment = 1,
            Geometry = 2,
            Program = 3
        };
        static const char* typeToString (const Type type);
        void checkError(const GLuint shader, const Type type) const;
        void loadShader(const char* path, std::string* code);

        GLuint id_;
};


#endif //GAMEENGINE_SHADER_H
