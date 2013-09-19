#version 120

uniform sampler2D sampler;

varying vec2 vTexCoord;

void main() {
	gl_FragColor = texture2D(sampler,vTexCoord);
}
