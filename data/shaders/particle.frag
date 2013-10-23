#version 420

uniform sampler2D textureSheet;

in vec2 v_texCoord;
in vec4 v_color;

void main() {
	gl_FragColor = v_color*texture2D(textureSheet,v_texCoord);
}
