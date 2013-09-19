#version 120

uniform mat4 modelViewProjectionMatrix;

attribute vec3 a_color;
attribute vec3 a_position;

varying vec3 vColor;

void main () {
        gl_Position = modelViewProjectionMatrix * vec4(a_position,1.0);
        vColor = a_color;
}
