//
// Created by Saul Moreno Abril on 10/01/2018.
//

#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>


using std::string;
using std::ios_base;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {

    string sVertexCode, sFragmentCode, sGeometryCode;
    loadShader(vertexPath, &sVertexCode);
    loadShader(fragmentPath, &sFragmentCode);
    if (geometryPath) {
        loadShader(geometryPath, &sGeometryCode);
    }

    const char* vertexCode = sVertexCode.c_str();
    const char* fragmentCode = sFragmentCode.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    checkError(vertex, Type::Vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    checkError(fragment, Type::Fragment);

    GLuint geometry;
    if (geometryPath) {
        const char *geometryCode = sGeometryCode.c_str();

        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometryCode, nullptr);
        glCompileShader(geometry);
        checkError(geometry, Type::Geometry);
    }

    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    if (geometryPath) {
        glAttachShader(id_, geometry);
    }
    glLinkProgram(id_);
    checkError(id_, Type::Program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath) {
        glDeleteShader(geometry);
    }
}


Shader::~Shader() {
    glDeleteProgram(id_);
}

void Shader::use() const {
    glUseProgram(id_);
}

const char* Shader::typeToString (const Shader::Type type) {
    switch (type) {
        case Shader::Type::Vertex:         return "Vertex";
        case Shader::Type::Fragment:   return "Fragment";
        case Shader::Type::Geometry:     return "Geometry";
        case Shader::Type::Program:           return "Program";
        default:
            break;
    }
    return "";
}

void Shader::checkError(const GLuint shader, const Type type) const {
    int success;
    char log[1024];
    if (type != Type::Program) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, log);
            const char *typeString = typeToString(type);
            cout << "Error Compiling Shader " << typeString << endl << log << endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, log);
            const char *typeString = typeToString(type);
            cout << "Error Compiling "<< typeString << endl << log << endl;
        }
    }
}

void Shader::loadShader(const char *path, std::string *code) {
    ifstream file;

    file.open(path, ios_base::in);
    if (file) {
        stringstream stream;
        stream << file.rdbuf();
        file.close();
        *code = stream.str();
    } else {
        cout << "Error Loading Shader " << path << endl;
    }

}


void Shader::set(const char* name, const bool value) const {
    glUniform1i(glGetUniformLocation(id_, name), value);
}

void Shader::set(const char* name, const GLint value) const {
    glUniform1i(glGetUniformLocation(id_, name),  value);

}

void Shader::set(const char* name, const GLuint value) const {
    glUniform1ui(glGetUniformLocation(id_, name), value);
}

void Shader::set(const char* name, const GLfloat value) const {
    glUniform1f(glGetUniformLocation(id_, name), value);
}

void Shader::set(const char* name, const GLfloat value0, const GLfloat value1) const {
    glUniform2f(glGetUniformLocation(id_, name), value0, value1);
}

void Shader::set(const char* name, const GLfloat value0, const GLfloat value1, const GLfloat value2) const {
    glUniform3f(glGetUniformLocation(id_, name), value0, value1, value2);
}

void Shader::set(const char* name, const GLfloat value0, const GLfloat value1, const GLfloat value2, const GLfloat value3) const {
    glUniform4f(glGetUniformLocation(id_, name), value0, value1, value2, value3);
}

void Shader::set(const char* name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

void Shader::set(const char* name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

void Shader::set(const char* name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

void Shader::set(const char* name, const glm::mat2& value) const {
    glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set(const char* name, const glm::mat3& value) const {
    glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set(const char* name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(value));
}