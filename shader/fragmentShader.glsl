#version 330 core

in vec2 textCoord;

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D tex;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
    vec3 ambient = material.ambient * light.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * material.diffuse * light.diffuse;


    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = spec * material.specular * light.specular;

    vec4 textColor = texture(tex, textCoord);
    vec3 phong = (ambient + diffuse + specular) * (textColor * color).rgb;


    fragColor = vec4(phong, textColor.a * color.a);

}