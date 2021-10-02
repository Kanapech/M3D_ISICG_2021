#version 450

layout( location = 0 ) out vec4 fragColor;

in vec4 colors;

uniform float light = 1;

void main() {
	//fragColor = vec4(1, 0, 0, 0);
	fragColor = colors*light;
}