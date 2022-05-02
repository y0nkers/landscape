#include "Engine.hpp"

namespace EngineSpace
{
  void Engine::initGLFW() const
  {
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Config::get().getMajorVersion());
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Config::get().getMinorVersion());
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  }

  void Engine::initGLEW() const
  {
      glewExperimental = GL_TRUE;
      if (glewInit() != GLEW_OK)
      throw std::runtime_error("Cant init GLEW");
  }

  void Engine::initDefaultOptionsGL() const
  {
      if (Config::get().getSamples() > 0) glEnable(GL_MULTISAMPLE); // Мультисемплирование
      glEnable(GL_DEPTH_TEST); // Тест глубины
      glDepthFunc(GL_LESS); // khronos.org/registry/OpenGL-Refpages/gl4/html/glDepthFunc.xhtml
      glEnable(GL_CULL_FACE); // Отсечение задних граней
      glEnable(GL_BLEND); // Включаем смешивание цветов
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Выбираем функцию смешивания цветов
      glEnable(GL_CLIP_DISTANCE0); // Делаем доступной плоскость отсечения (gl_ClipDistance[0] в шейдере)
  }

  void Engine::initDeltaTime()
  {
      float currentTime = glfwGetTime();
	  deltaTime = currentTime - lastTime;
	  lastTime = currentTime;
  }

  void Engine::calcFPS()
  {
	  float currentTime = glfwGetTime();
	  if ((currentTime - lastTimeFromShow) > 1)
	  {
		  actualFPS = std::to_string(frames) + " FPS";
		  frames = 0;
		  lastTimeFromShow = currentTime;
	  }
	  else ++frames;
  }

#if DEBUG_ENGINE == 1
  void Engine::showErrors()
  {
	  GLenum err;
	  while ((err = glGetError()) != GL_NO_ERROR)
		  std::cout << "GL error code: " << err << std::endl;
  }
#endif
}
