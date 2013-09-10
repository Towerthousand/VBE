#version 420

uniform sampler2D sampler;

in vec3 vColor;
in vec2 vTexCoord;

void main() {
	gl_FragColor = texture(sampler,vTexCoord);
}
