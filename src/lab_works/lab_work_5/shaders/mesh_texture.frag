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
uniform bool uHasNormalMap;

layout( binding = 1 ) uniform sampler2D uDiffuseMap;
layout( binding = 2 ) uniform sampler2D uAmbiantMap;
layout( binding = 3 ) uniform sampler2D uSpecularMap;
layout( binding = 4 ) uniform sampler2D uShininessMap;
layout( binding = 5 ) uniform sampler2D uNormalMap;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;
in vec3 tangentLightPos;
//in vec3 tangentViewPos; ( Inutile );
in vec3 tangentFragPos;

void main()
{
	
	vec3 normalM = normal;

	vec3 diffuse = uDiffuse;
	vec3 ambient = uAmbient;
	vec3 specular = uSpecular;
	float shininess = uShininess;
	vec3 lightDir = normalize( vec3( 0.f ) - fragPos );

	if( uHasNormalMap ){
		normalM = texture( uNormalMap, texCoords ).xyz ;
		normalM = normalize( normalM * 2.0 - 1.0 );

		lightDir = normalize( tangentLightPos - tangentFragPos );
	}
	if( uHasDiffuseMap ){
		diffuse = texture(uDiffuseMap, texCoords).xyz;
	}
	if( uHasAmbientMap ){
		ambient = texture(uAmbiantMap, texCoords).xyz;
	}
	if( uHasSpecularMap ){
		specular = texture(uSpecularMap, texCoords).xxx;
	}
	if( uHasShininessMap ){
		shininess = texture(uShininessMap, texCoords).x;
	}

	
	vec3 diff = diffuse * max( dot( normalM, lightDir), 0.f );

	// la lumière est au même endroit que la caméra donc on normalize la valeur doublée
	vec3 spec = specular * pow( max( dot( normalM, normalize( lightDir + lightDir ) ), 0.f ), shininess );

	vec3 res = spec + diff + ambient;

	fragColor = vec4( res, 1.f );

	

	
}
