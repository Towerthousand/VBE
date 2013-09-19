#version 120

varying vec3 vColor;

void main() {
    float m = max(vColor.r, max(vColor.g, vColor.b));
	gl_FragColor = vec4(floor((vColor/m)*4.01)/4.0, 1.0);
}
