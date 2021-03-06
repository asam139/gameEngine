#version 330 core

in vec2 text_coord;

in vec3 P;
in vec3 N1;
in vec3 V1;

out vec4 frag_color;

struct Material {
    vec3 ambient_color;

    vec3 diffuse_color;
    sampler2D diffuse_text;

    sampler2D specular_text;
    vec3 specular_color;

    float shininess;

    bool emission_active;
    sampler2D emissive_text;
    vec3 emissive_color;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;


void main() {
    // Calculate light vector
    vec3 L1 = light.position - P.xyz;

    // Normalize the incoming N, L, and V vectors
    vec3 N = normalize(N1);
    vec3 L = normalize(L1);
    vec3 V = normalize(V1);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);

    // Get Textures
    vec3 diff_tex = vec3(texture(material.diffuse_text, text_coord));
    vec3 spec_tex = vec3(texture(material.specular_text, text_coord));

    // Calculate ambient, difusse, specular contribution
    vec3 ambient = diff_tex * material.ambient_color * light.ambient;
    vec3 diffuse  = diff_tex * material.diffuse_color * light.diffuse * max(0.0, dot(N, L));
    vec3 specular = spec_tex * material.specular_color * light.specular * pow(max(0.0, dot(R, V)), material.shininess);

    // Calculate Emission
    vec3 emission = vec3(0.0);
    if (material.emission_active) {
        vec3 emis_tex = vec3(texture(material.emissive_text, text_coord));
        emission = emis_tex * material.emissive_color;
    }

    vec3 phong = ambient + diffuse + specular + emission;

    frag_color = vec4(phong, 1.0);
}