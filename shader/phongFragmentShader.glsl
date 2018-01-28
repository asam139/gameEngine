#version 330 core

in vec2 text_coord;

in vec3 N1;
in vec3 L1;
in vec3 V1;

out vec4 frag_color;

uniform vec3 color = vec3(1.0, 1.0, 1.0);

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;


void main() {
    // Normalize the incoming N, L, and V vectors
    vec3 N = normalize(N1);
    vec3 L = normalize(L1);
    vec3 V = normalize(V1);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);

    // Get Textures
    vec3 diff_tex = vec3(texture(material.diffuse, text_coord));
    vec3 spec_tex = vec3(texture(material.specular, text_coord));

    // Calculate ambient, difusse, specular contribution
    vec3 ambient = light.ambient * diff_tex;
    vec3 diffuse  = diff_tex * light.diffuse * max(0.0, dot(N, L));
    vec3 specular = spec_tex * light.specular * pow(max(0.0, dot(R, V)), material.shininess);

    vec3 phong = ambient + diffuse + specular;

    frag_color = vec4(phong * color, 1.0);
}