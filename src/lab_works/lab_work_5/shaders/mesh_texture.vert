#version 450

layout( location = 0 ) in vec3 aVertexPosition;
layout( location = 1 ) in vec3 aVertexNormal;
layout( location = 2 ) in vec2 aVertexTexCoords;
layout( location = 3 ) in vec3 aVertexTangent;
layout( location = 4 ) in vec3 aVertexBitagent;

uniform mat4 uMVPMatrix; // Projection * View * Model
uniform mat4 uNormalMatrix;
uniform mat4 uMVMatrix;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoords;

void main()
{
	gl_Position = uMVPMatrix * vec4( aVertexPosition, 1.f );
	normal = normalize( mat3(uNormalMatrix) * aVertexNormal );
	fragPos = vec3( uMVMatrix * vec4(aVertexPosition, 1.f));
	texCoords = aVertexTexCoords;
}
