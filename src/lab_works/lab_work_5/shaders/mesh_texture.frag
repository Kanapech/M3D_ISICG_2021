#version 450

layout( location = 0 ) out vec4 fragColor;

uniform vec3 uAmbient;
uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uExp;
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
	
	if( uHasDiffuseMap == true ){
		vec4 diffuse = texture(uDiffuseMap, texCoords);
		fragColor = diffuse;
	}
	else if( uHasAmbientMap == true ){
		vec4 ambiant = texture(uAmbiantMap, texCoords);
		fragColor = ambiant;
	}
	else if( uHasSpecularMap == true ){
		vec3 specular = texture(uSpecularMap, texCoords).xxx;
		fragColor = vec4( specular, 1.f );
	}
	else if( uHasShininessMap == true ){
		float shininess = texture(uShininessMap, texCoords).x;
		fragColor = vec4( shininess );
	}
	else{
		vec3 lightDir = normalize( vec3( 0.f ) - fragPos );
		vec3 diff = uDiffuse * max( dot( normal, lightDir), 0.f );

		// la lumière est au même endroit que la caméra donc on normalize la valeur doublée
		vec3 spec = uSpecular * pow( max( dot( normal, normalize( lightDir + lightDir ) ), 0.f ), uExp );

		vec3 res = spec + diff + uAmbient;

		fragColor = vec4( res, 1.f );
	}
	

	
}
