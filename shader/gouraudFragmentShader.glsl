#version 330 core

 in vec2 textCoord;
 in vec3 vColor;

 out vec4 fragColor;

 uniform sampler2D tex;

 void main() {
     vec3 textColor = texture(tex, textCoord).rgb;
     fragColor = vec4(textColor * vColor, 1.0);
 }