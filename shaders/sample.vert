#version 420

uniform mat4 modelViewProjectionMatrix;

in vec3 a_position;
in vec3 a_color;

out vec3 vColor;

void main () {
        gl_Position = modelViewProjectionMatrix * vec4(a_position,1.0);
        vColor = a_color;
}
