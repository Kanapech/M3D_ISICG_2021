#ifndef __LAB_WORK_2_HPP__
#define __LAB_WORK_2_HPP__

#include "GL/gl3w.h"
#include "common/base_lab_work.hpp"
#include "define.hpp"
#include <vector>

namespace M3D_ISICG
{
	class LabWork2 : public BaseLabWork
	{
	  public:
		LabWork2() : BaseLabWork() {}
		~LabWork2();

		bool init() override;
		void animate( const float p_deltaTime ) override;
		void render() override;

		void handleEvents( const SDL_Event & p_event ) override;
		void displayUI() override;

	  private:
		// ================ Scene data.
		std::vector<Vec2f> triangle;
		std::vector<int> sommets;
		std::vector<Vec3f> couleurs;

		// ================

		// ================ GL data.
		GLuint vertexShader;
		GLuint fragmentShader;

		GLuint program;

		GLuint vbo;
		GLuint vao;
		GLuint ebo;
		GLuint vboCouleurs;
		GLint  translationLoc;
		GLint  lightLoc;
		// ================

		// ================ Settings.
		Vec4f _bgColor = Vec4f( 0.8f, 0.8f, 0.8f, 1.f ); // Background color
		float _time;
		float brightness;
		// ================

		static const std::string _shaderFolder;
	};
} // namespace M3D_ISICG

#endif // __LAB_WORK_2_HPP__
