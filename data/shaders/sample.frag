#version 420

uniform sampler2D sampler;

in vec3 vColor;
in vec2 vTexCoord;

void main() {
	gl_FragColor = texture(sampler,vTexCoord)*0.5 + vec4(vColor,1.0)*0.5;
}
