#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;
layout (location = 2) in vec3 aNormal;

out vec2 text_coord;
out vec3 vertex_Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_mat;

uniform vec3 light_position = vec3(0.0, 0.0, 0.0);
uniform vec3 light_color = vec3(0.75, 0.75, 0.75);
uniform vec3 ambient_color = vec3(1.0);

uniform vec3 view_position;

uniform float ambient_strenght = 0.1;
uniform float diffuse_strenght = 1.0;
uniform float specular_strenght = 0.35;
uniform int shininess = 32;

void main() {
    // Calculate normal in view space
    vec3 P = vec3(model * vec4(aPos, 1.0));

    // Calculate normal in view space
    vec3 normal = normal_mat * aNormal;
    vec3 N = normalize(mat3(model) * normal);

    // Calculate view-space light vector
    vec3 L = normalize(light_position - P);

    // Calculate view vector (simply the negtive of the view-space position)
    vec3 V = normalize(view_position - P);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);

    // Calculate ambient, diffuse, specular contribution
    //vec3 ambient = ambient_strenght * light_color;
    vec3 diffuse = diffuse_strenght * light_color * max(0.0, dot(N, L));
    //vec3 specular = specular_strenght * light_color * pow(max(0.0, dot(R, V)), shininess);

    //vec3 gouraud = ambient + diffuse + specular;
    vec3 flatt = diffuse;

    // Seed text coord
    text_coord = aTextCoord;

    // Send the color output to the fragment shader
    vertex_Color = flatt;

    // Calculate the clip-space position of each vertex
    gl_Position = projection * view * model * vec4(aPos, 1.f);

}