#version 450

layout( location = 0 ) out vec4 fragColor;

uniform vec3 uAmbient;
uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uExp;

in vec3 normal;
in vec3 fragPos;

void main()
{
	vec3 lightDir = normalize( vec3( 0.f ) - fragPos );
	vec3 diff = uDiffuse * max( dot( normal, lightDir), 0.f );

	// la lumière est au même endroit que la caméra donc on normalize la valeur doublée
	vec3 spec = uSpecular * pow( max( dot( normal, normalize( lightDir + lightDir ) ), 0.f ), uExp );

	vec3 res = spec + diff + uAmbient;

	fragColor = vec4( res, 1.f );
}
