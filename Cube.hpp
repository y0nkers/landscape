#ifndef CUBE_HPP
#define CUBE_HPP 1
#include "Shape.hpp"

namespace EngineSpace
{
	class Cube : public Shape
	{
	public:
		Cube();
		virtual void render(Program& program);
		virtual void render(Program& program, const unsigned& amount);
	};
}
#endif
