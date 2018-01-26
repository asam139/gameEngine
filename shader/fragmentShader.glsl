#version 330 core

in vec2 textCoord;

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 viewPos;

void main() {
    vec3 diffTex = vec3(texture(material.diffuse, textCoord));
    vec3 specTex = vec3(texture(material.specular, textCoord));

    vec3 ambient = light.ambient * diffTex;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * diffTex * light.diffuse;


    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = spec * specTex * light.specular;


    vec3 phong = (ambient + diffuse + specular) * color.rgb;


    fragColor = vec4(phong, color.a);
}