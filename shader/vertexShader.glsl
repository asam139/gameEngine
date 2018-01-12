#version 330core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float time;
uniform vec3 refPoint;

out vec3 myColor;

#define PI 3.141592653589793
#define HALF_PI 1.5707963267948966

void main() {
    gl_Position = vec4(aPos.x + refPoint.x, aPos.y + refPoint.y, aPos.z + refPoint.z, 1.f);

    //To debug paint pos as color.
    //Use abs because it does not exist negative values
    myColor =  abs(aPos);
    //myColor = vec3(sin(time * aColor.r), sin(time * aColor.g + HALF_PI/2.f) ,  cos(time * aColor.b));
}