#version 450

layout( location = 0 ) out vec4 fragColor;

uniform vec3 uAmbient;
uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uShininess;
uniform bool uHasDiffuseMap;
uniform bool uHasAmbientMap;
uniform bool uHasSpecularMap;
uniform bool uHasShininessMap;

layout( binding = 1 ) uniform sampler2D uDiffuseMap;
layout( binding = 2 ) uniform sampler2D uAmbiantMap;
layout( binding = 3 ) uniform sampler2D uSpecularMap;
layout( binding = 4 ) uniform sampler2D uShininessMap;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

void main()
{
	
	vec3 diffuse = uDiffuse;
	vec3 ambient = uAmbient;
	vec3 specular = uSpecular;
	float shininess = uShininess;

	if( uHasDiffuseMap ){
		diffuse = vec3(texture(uDiffuseMap, texCoords));
	}
	if( uHasAmbientMap ){
		ambient = vec3(texture(uAmbiantMap, texCoords));
	}
	if( uHasSpecularMap ){
		specular = texture(uSpecularMap, texCoords).xxx;
	}
	if( uHasShininessMap ){
		shininess = texture(uShininessMap, texCoords).x;
	}

	vec3 lightDir = normalize( vec3( 0.f ) - fragPos );
	vec3 diff = diffuse * max( dot( normal, lightDir), 0.f );

	// la lumière est au même endroit que la caméra donc on normalize la valeur doublée
	vec3 spec = specular * pow( max( dot( normal, normalize( lightDir + lightDir ) ), 0.f ), shininess );

	vec3 res = spec + diff + ambient;

	fragColor = vec4( res, 1.f );

	

	
}
