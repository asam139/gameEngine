#version 330 core

in vec2 textCoord;

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform sampler2D tex;

uniform vec3 lightPos;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform float ambientStrenght = 0.1;

uniform vec3 viewPos;
uniform int shininess;
uniform float specularStrenght;

void main() {
    vec3 ambient = ambientStrenght * lightColor.rgb;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor.rgb;


    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec3 specular = specularStrenght * spec * lightColor;

    vec3 textColor = texture(tex, textCoord).rgb;
    vec3 phong = (ambient + diffuse + specular) * (textColor * color);

    fragColor = vec4(phong, 1.0);
}