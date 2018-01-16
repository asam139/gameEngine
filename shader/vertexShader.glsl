#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

out vec3 myColor;
out vec2 textCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 transform;


void main() {
    gl_Position = projection * view * model * transform * vec4(aPos, 1.f);
    myColor = aColor;
    textCoord = aTextCoord;
}