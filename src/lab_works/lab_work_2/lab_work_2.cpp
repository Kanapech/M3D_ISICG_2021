#include "imgui.h"
#include "lab_work_2.hpp"
#include "utils/read_file.hpp"
#include <iostream>
#include "glm/gtc/type_ptr.hpp"

namespace M3D_ISICG
{
	const std::string LabWork2::_shaderFolder = "src/lab_works/lab_work_2/shaders/";

	LabWork2::~LabWork2()
	{
		glDeleteShader( vertexShader );
		glDeleteShader( fragmentShader );

		glDeleteProgram( program );

		glDeleteBuffers( 1, &vbo );
		glDeleteBuffers( 1, &vao );
		glDeleteBuffers( 1, &ebo );
		glDeleteBuffers( 1, &vboCouleurs );

		glDisableVertexArrayAttrib( vao, 0 );
		glDeleteVertexArrays( 1, &vao );
	}

	bool LabWork2::init()
	{
		const std::string vertexShaderStr	= readFile( _shaderFolder + "lw2.vert" );
		const std::string fragmentShaderStr = readFile( _shaderFolder + "lw2.frag" );

		vertexShader   = glCreateShader( GL_VERTEX_SHADER );
		fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

		const GLchar * vSrc = vertexShaderStr.c_str();
		const GLchar * fSrc = fragmentShaderStr.c_str();

		_time = 0;
		brightness = 1;

		glShaderSource( vertexShader, 1, &vSrc, NULL );
		glShaderSource( fragmentShader, 1, &fSrc, NULL );

		glCompileShader( vertexShader );
		glCompileShader( fragmentShader );

		// Check if compilation is ok.
		GLint compiled;
		glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &compiled );
		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( vertexShader, sizeof( log ), NULL, log );
			glDeleteShader( vertexShader );
			glDeleteShader( fragmentShader );
			std::cerr << "Error compiling vertex shader: " << log << std::endl;
			return false;
		}

		// Check if compilation is ok.

		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &compiled );
		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( fragmentShader, sizeof( log ), NULL, log );
			glDeleteShader( vertexShader );
			glDeleteShader( fragmentShader );
			std::cerr << "Error compiling vertex shader: " << log << std::endl;
			return false;
		}

		program = glCreateProgram();

		glAttachShader( program, vertexShader );
		glAttachShader( program, fragmentShader );

		glLinkProgram( program );

		// Check if link is ok.
		GLint linked;
		glGetProgramiv( program, GL_LINK_STATUS, &linked );
		if ( !linked )
		{
			GLchar log[ 1024 ];
			glGetProgramInfoLog( program, sizeof( log ), NULL, log );
			std::cerr << "Error linking program: " << log << std::endl;
			return false;
		}

		triangle = { { -0.5, 0.5 }, { 0.5, 0.5 }, { 0.5, -0.5 }, { -0.5, -0.5 } };
		sommets	 = { 0, 1, 2, 2, 3, 0 };
		couleurs = { { 1.f, 0.f, 0.f }, { 0.f, 1.f, 0.f }, { 0.f, 0.f, 1.f }, { 1.f, 0.f, 1.f } };

		glCreateBuffers( 1, &vbo );
		glNamedBufferData( vbo, triangle.size() * sizeof( Vec2f ), triangle.data(), GL_STATIC_DRAW );

		glCreateBuffers( 1, &ebo );
		glNamedBufferData( ebo, sommets.size() * sizeof(int), sommets.data(), GL_STATIC_DRAW );

		glCreateBuffers( 1, &vboCouleurs );
		glNamedBufferData( vboCouleurs, couleurs.size() * sizeof( Vec3f ), couleurs.data(), GL_STATIC_DRAW );

		glCreateVertexArrays( 1, &vao );
		glEnableVertexArrayAttrib( vao, 0 );
		glEnableVertexArrayAttrib( vao, 1 );
		glVertexArrayAttribFormat( vao, 0, 2, GL_FLOAT, GL_FALSE, 0 );

		glVertexArrayVertexBuffer( vao, 0, vbo, 0, sizeof( float ) * 2 );
		glVertexArrayElementBuffer( vao, ebo );
		glVertexArrayVertexBuffer( vao, 1, vboCouleurs, 0, sizeof( float ) * 3 );

		translationLoc = glGetUniformLocation( program, "uTranslationX" );
		lightLoc = glGetUniformLocation( program, "light" );


		glUseProgram( program );

		std::cout << "Initializing lab work 2..." << std::endl;
		// Set the color used by glClear to clear the color buffer (in render()).
		glClearColor( _bgColor.x, _bgColor.y, _bgColor.z, _bgColor.w );

		std::cout << "Done!" << std::endl;
		return true;
	}

	void LabWork2::animate( const float p_deltaTime ) {
		glProgramUniform1f( program, translationLoc, glm::sin(_time) );
		_time += p_deltaTime;
	}

	void LabWork2::render()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glBindVertexArray( vao );
		//glDrawArrays( GL_TRIANGLES, 0, 3 );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
	}

	void LabWork2::handleEvents( const SDL_Event & p_event ) {}

	void LabWork2::displayUI()
	{
		ImGui::Begin( "Settings lab work 2" );
		if (ImGui::SliderFloat("Brightness", &brightness, 0, 1)) {
			glProgramUniform1f( program, lightLoc, brightness );
		}

		if (ImGui::ColorEdit3("Background Color", glm::value_ptr(_bgColor))) {
			glClearColor( _bgColor.x, _bgColor.y, _bgColor.z, _bgColor.w );
		}
		
		
		ImGui::End();
	}

} // namespace M3D_ISICG
