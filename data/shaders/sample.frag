#version 420

uniform sampler2D sampler;

in vec2 vTexCoord;

void main() {
	gl_FragColor = vec4(texture2D(sampler,vTexCoord).xyz,0.5);
}
