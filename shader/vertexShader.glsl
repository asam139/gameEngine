#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;
layout (location = 2) in vec3 aNormal;

out vec2 textCoord;

out vec3 N1;
out vec3 L1;
out vec3 V1;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_mat;

uniform vec3 light_position = vec3(0.0, 0.0, 0.0);

uniform vec3 view_position;


void main() {
    // Calculate view-space coordinate
    vec3 P = vec3(model * vec4(aPos, 1.0));

    // Calculate normal in view-space
    vec3 normal = normal_mat * aNormal;
    N1 = mat3(model) * normal;

    // Calculate light vector
    L1 = light_position - P.xyz;

    // Calculate view vector
    V1 = view_position - P.xyz;

    // Seed text coord
    textCoord = aTextCoord;

    // Calculate the clip-space position of each vertex
    gl_Position = projection * view * vec4(P, 1.0);
}