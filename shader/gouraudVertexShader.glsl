#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;
layout (location = 2) in vec3 aNormal;

out vec2 textCoord;
out vec3 vColor;

uniform vec3 color = vec3(1.0, 1.0, 1.0);

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

uniform vec3 lightPos;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform float ambientStrenght = 0.1;

uniform vec3 viewPos;
uniform int shininess;
uniform float specularStrenght;

void main() {
    vec3 normal = normalMat * aNormal;
    vec3 fragPos = vec3(model * vec4(aPos, 1.0));

    vec3 ambient = ambientStrenght * lightColor.rgb;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor.rgb;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec3 specular = specularStrenght * spec * lightColor;

    vec3 phong = (ambient + diffuse + specular) * color;

    gl_Position = projection * view * model * vec4(aPos, 1.f);
    textCoord = aTextCoord;
    vColor = phong;
}