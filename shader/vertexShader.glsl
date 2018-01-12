#version 330core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float uniformTime;

out vec3 myColor;

#define PI 3.141592653589793
#define HALF_PI 1.5707963267948966

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.f);
    myColor = vec3(sin(uniformTime * aColor.r), sin(uniformTime * aColor.g + HALF_PI/2.f) ,  cos(uniformTime * aColor.b));
}