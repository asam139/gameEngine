#version 330 core

in vec2 text_coord;
in vec3 vertex_Color;

out vec4 frag_color;

uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform sampler2D tex;

void main() {
    vec3 text_color = texture(tex, text_coord).rgb;
    frag_color = vec4(vertex_Color * color * text_color, 1.0);
}