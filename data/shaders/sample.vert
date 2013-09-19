#version 120

uniform mat4 modelViewProjectionMatrix;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

varying vec2 vTexCoord;

void main () {
		gl_Position = modelViewProjectionMatrix * vec4(a_position,1.0);
		vTexCoord = a_texCoord;
}
