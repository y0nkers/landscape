#ifndef SKYBOX_HPP
#define SKYBOX_HPP 1
#include "Texture.hpp"
#include "Cube.hpp"

namespace EngineSpace
{
	class Skybox : public Shape
	{
		Texture texture;
		void init();

	public:
		Skybox() { init(); }
		Skybox(const Texture& tex) :texture(tex) { init(); }

		virtual void render(Program& program);

		Texture& getTexture() { return texture; }
	};
}
#endif
