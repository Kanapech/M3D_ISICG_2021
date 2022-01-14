#version 450

layout( location = 0 ) in vec3 aVertexPosition;
layout( location = 1 ) in vec3 aVertexNormal;
layout( location = 2 ) in vec2 aVertexTexCoords;
layout( location = 3 ) in vec3 aVertexTangent;
layout( location = 4 ) in vec3 aVertexBitangent;

uniform mat4 uMVPMatrix; // Projection * View * Model
uniform mat4 uNormalMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uModelMatrix;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoords;

out vec3 tangentLightPos;
//out vec3 tangentViewPos;
out vec3 tangentFragPos;

void main()
{
	gl_Position = uMVPMatrix * vec4( aVertexPosition, 1.f );
	normal = normalize( mat3(uNormalMatrix) * aVertexNormal );
	fragPos = vec3( uMVMatrix * vec4(aVertexPosition, 1.f));
	texCoords = aVertexTexCoords;
	/*vec3 T = vec3(uMVMatrix * normalize( vec4(aVertexTangent, 0.0) ) );
	vec3 B = vec3(uMVMatrix * normalize( vec4(aVertexBitagent, 0.0) ) );
	vec3 N = vec3(uMVMatrix * normalize( vec4(aVertexNormal, 0.0) ) );
	mat3 TBNView = mat3(T, B, N);
	TBNView = transpose( mat3( T, B, N ) );*/

	vec3 T = normalize(vec3(uMVMatrix * vec4(aVertexTangent,   0.0)));
	vec3 B = normalize(vec3(uMVMatrix * vec4(aVertexBitangent, 0.0)));
	vec3 N = normalize(vec3(uMVMatrix * vec4(aVertexNormal,    0.0)));
	mat3 TBN = mat3(T, B, N);

	mat3 inv_TBN = transpose( TBN );

	vec3 tangentLightPos = inv_TBN * vec3(0, 0, 0);// Lumière = vec3(0, 0, 0) ici
	//vec3 tangentViewPos = inv_TBN * vec3(0, 0, 0); // (Inutile ici)
	vec3 tangentFragPos = inv_TBN * vec3( uMVMatrix * vec4( aVertexPosition, 1.0 ) );
}
