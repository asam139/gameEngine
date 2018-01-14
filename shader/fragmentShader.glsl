#version 330core

in vec3 myColor;
in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    //vec4 mixTexture = mix(texture(texture1, textCoord), texture(texture2, textCoord), 0.5f);
    //fragColor = mix(mixTexture, vec4(myColor, 1.f), 0.5f);

    fragColor = texture(texture1, textCoord);
}