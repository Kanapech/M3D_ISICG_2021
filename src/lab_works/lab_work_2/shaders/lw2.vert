#version 450

layout( location = 0 ) in vec2 aVertexPosition;
layout( location = 1 ) in vec3 aColors;

out vec4 colors;

uniform float uTranslationX;

void main() {

	gl_Position = vec4(aVertexPosition.x+uTranslationX, aVertexPosition.y, 0, 1.f);
	colors = vec4(aColors, 0.f);
}
