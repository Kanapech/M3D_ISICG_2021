#include "triangle_mesh.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

namespace M3D_ISICG
{
	TriangleMesh::TriangleMesh( const std::string &				  p_name,
								const std::vector<Vertex> &		  p_vertices,
								const std::vector<unsigned int> & p_indices,
								const Material &				  p_material ) :
		_name( p_name ),
		_vertices( p_vertices ), _indices( p_indices ), _material( p_material )
	{
		_vertices.shrink_to_fit();
		_indices.shrink_to_fit();
		_setupGL();
	}

	void TriangleMesh::render( const GLuint p_glProgram ) const
	{
		glEnable( GL_DEPTH_TEST );
		// Clear the color buffer.
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glBindVertexArray( _vao );

		GLint _uAmbientLoc = glGetUniformLocation( p_glProgram, "uAmbient" );
		glProgramUniform3fv( p_glProgram, _uAmbientLoc, 1, glm::value_ptr( _material._ambient ) );

		GLint _uDiffuseLoc = glGetUniformLocation( p_glProgram, "uDiffuse" );
		glProgramUniform3fv( p_glProgram, _uDiffuseLoc, 1, glm::value_ptr( _material._diffuse ) );

		GLint _uSpecularLoc = glGetUniformLocation( p_glProgram, "uSpecular" );
		glProgramUniform3fv( p_glProgram, _uSpecularLoc, 1, glm::value_ptr( _material._specular ) );
		
		GLint _uExpLoc = glGetUniformLocation( p_glProgram, "uExp" );
		glProgramUniform1f( p_glProgram, _uExpLoc, _material._shininess );

		glDrawElements( GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
	}

	void TriangleMesh::cleanGL()
	{
		glDisableVertexArrayAttrib( _vao, 0 );
		glDisableVertexArrayAttrib( _vao, 1 );
		glDisableVertexArrayAttrib( _vao, 2 );
		glDisableVertexArrayAttrib( _vao, 3 );
		glDisableVertexArrayAttrib( _vao, 4 );
		glDeleteVertexArrays( 1, &_vao );
		glDeleteBuffers( 1, &_vbo );
		glDeleteBuffers( 1, &_ebo );
	}

	void TriangleMesh::_setupGL()
	{	
		glCreateBuffers( 1, &_vbo );
		glNamedBufferData(
			_vbo, _vertices.size() * sizeof( Vertex ), _vertices.data(), GL_STATIC_DRAW );

		glCreateBuffers( 1, &_ebo );
		glNamedBufferData( _ebo, _indices.size() * sizeof( unsigned int ), _indices.data(), GL_STATIC_DRAW );

		glCreateVertexArrays( 1, &_vao );
		glEnableVertexArrayAttrib( _vao, 0 );
		glEnableVertexArrayAttrib( _vao, 1 );
		glEnableVertexArrayAttrib( _vao, 2 );
		glEnableVertexArrayAttrib( _vao, 3 );
		glEnableVertexArrayAttrib( _vao, 4 );

		glVertexArrayAttribFormat( _vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof( Vertex, _position) );
		glVertexArrayAttribFormat( _vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof( Vertex, _normal ) );
		glVertexArrayAttribFormat( _vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof( Vertex, _texCoords ) );
		glVertexArrayAttribFormat( _vao, 3, 3, GL_FLOAT, GL_FALSE, offsetof( Vertex, _tangent ) );
		glVertexArrayAttribFormat( _vao, 4, 3, GL_FLOAT, GL_FALSE, offsetof( Vertex, _bitangent ) );

		glVertexArrayVertexBuffer( _vao, 0, _vbo, 0, sizeof(Vertex) );
		glVertexArrayVertexBuffer( _vao, 1, _vbo, 0, sizeof( Vertex ) );
		glVertexArrayVertexBuffer( _vao, 2, _vbo, 0, sizeof( Vertex ) );
		glVertexArrayVertexBuffer( _vao, 3, _vbo, 0, sizeof( Vertex ) );
		glVertexArrayVertexBuffer( _vao, 4, _vbo, 0, sizeof( Vertex ) );

		glVertexArrayElementBuffer( _vao, _ebo );

	}
} // namespace M3D_ISICG
