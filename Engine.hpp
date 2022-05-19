// GLEW library - http://glew.sourceforge.net
// GLFW library - https://www.glfw.org
// GLM library - https://glm.g-truc.net
// Assimp library - https://github.com/assimp/assimp
// FreeType library - https://www.freetype.org
// STB_IMAGE library - https://github.com/nothings/stb

#ifndef ENGINE_HPP
#define ENGINE_HPP 1
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Singleton.hpp"
#include "Config.hpp"

namespace EngineSpace
{
	class Engine : public Singleton<Engine>
	{
		friend class Singleton<Engine>;
		float lastTimeFromShow = 0; // Последнее время с показа кадра
		unsigned frames = 0; // fps
		float lastTime = 0;
		float deltaTime = 0;
		std::string actualFPS;

		Engine() {}

	public:
		void initGLFW() const;
		void initGLEW() const;
		void initDefaultOptionsGL() const;
		void initDeltaTime();
		void calcFPS();

#if DEBUG_ENGINE == 1
		void showErrors();
#endif

		float getDeltaTime() const { return deltaTime; }
		std::string getFPS() const { return actualFPS; }
		unsigned getFrames() const { return frames; }
	};
}
#endif
