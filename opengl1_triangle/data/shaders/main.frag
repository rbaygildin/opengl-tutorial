#version 410

uniform vec4 outColor;
out vec4 frag_color;

void main() {
	frag_color = outColor;
}
