#version 330core

in vec3 myColor;
in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D texture1;

void main() {
    fragColor = texture(texture1, textCoord) + vec4(myColor, 1.f);
}