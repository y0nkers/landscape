#include "Window.hpp"

namespace EngineSpace
{
	void Window::create(bool isFullscreen)
	{
		if (isCreate()) return;

		Engine::get().initGLFW();
		float samples = Config::get().getSamples();
		if (samples > 0) glfwWindowHint(GLFW_SAMPLES, samples); // Сглаживание с помощью сэмплирования
		window = glfwCreateWindow(width, height, title.c_str(), isFullscreen? glfwGetPrimaryMonitor() : nullptr, nullptr);
		
		if (!window) throw std::runtime_error("Cant create GLFW window.");
		
		glfwMakeContextCurrent(window);
		Engine::get().initGLEW();
		Engine::get().initDefaultOptionsGL();
		glViewport(0, 0, width, height);
	}

	void Window::open()
	{
		if (loopCallback == nullptr) loopCallback = []()->void {};

		while (!glfwWindowShouldClose(window))
		{
			Engine::get().initDeltaTime();
			inputCallback(window);
			loopCallback();

#if DEBUG_ENGINE == 1
			Engine::get().showErrors();
#endif

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}

	void Window::close() { glfwSetWindowShouldClose(window, true); }

	void Window::setSize(const unsigned& w, const unsigned& h)
	{
		width = w;
		height = h;
		glViewport(0, 0, w, h);
	}

	void Window::setTitle(const std::string& t)
	{
		title = t;
		glfwSetWindowTitle(window, title.c_str());
	}
}
