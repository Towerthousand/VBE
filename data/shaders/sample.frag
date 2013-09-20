#version 420

uniform sampler2D sampler;

in vec2 vTexCoord;

void main() {
	gl_FragColor = texture2D(sampler,vTexCoord);
}
