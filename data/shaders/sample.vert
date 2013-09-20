#version 420

uniform mat4 modelViewProjectionMatrix;

in vec3 a_position;
in vec3 a_normal;
in vec2 a_texCoord;

out vec2 vTexCoord;

void main () {
		gl_Position = modelViewProjectionMatrix * vec4(a_position,1.0);
		vTexCoord = a_texCoord;
}
