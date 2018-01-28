#version 330 core

in vec2 textCoord;

in vec3 N1;
in vec3 L1;
in vec3 V1;

out vec4 frag_color;


uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform sampler2D tex;

uniform vec3 light_color = vec3(0.75, 0.75, 0.75);
uniform vec3 ambient_color = vec3(1.0);

uniform float ambient_strenght = 0.1;
uniform float diffuse_strenght = 0.5;
uniform float specular_strenght = 0.35;
uniform int shininess = 32;


void main() {
    // Normalize the incoming N, L, and V vectors
    vec3 N = normalize(N1);
    vec3 L = normalize(L1);
    vec3 V = normalize(V1);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);

    // Calculate ambient, difusse, specular contribution
    vec3 ambient  = ambient_strenght * ambient_color;
    vec3 diffuse  = diffuse_strenght * light_color * max(0.0, dot(N, L));
    vec3 specular = specular_strenght * light_color * pow(max(0.0, dot(R, V)), shininess);

    vec3 phong = ambient + diffuse + specular;

    vec3 text_color = texture(tex, textCoord).rgb;
    frag_color = vec4(phong * text_color * color, 1.0);
}