#version 330 core

in vec2 textCoord;

in vec3 normal;
in vec3 fragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

out vec4 fragColor;

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D tex;

uniform vec3 lightPos;
uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 viewPos;

void main() {
    vec3 ambient = material.ambient * lightColor.rgb;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * material.diffuse * lightColor.rgb;


    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = spec * material.specular * lightColor.rgb;

    vec4 textColor = texture(tex, textCoord);
    vec3 phong = (ambient + diffuse + specular) * (textColor * color).rgb;


    fragColor = vec4(phong, textColor.a * color.a);

}