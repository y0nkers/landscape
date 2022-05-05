#ifndef WINDOW_HPP
#define WINDOW_HPP 1

#include <stdexcept>
#include "Engine.hpp"

namespace EngineSpace
{
	class Window
	{
		GLFWwindow* window = nullptr;
		unsigned width;
		unsigned height;
		std::string title;

		void (*loopCallback)() = nullptr; // Основной цикл
		void (*inputCallback)(GLFWwindow*) = nullptr; // Обработка ввода данных пользователем

	public:
		Window(const unsigned& pWidth = Config::get().getWindowWidth(),
			const unsigned& pHeight = Config::get().getWindowHeight(),
			const std::string& pTitle = Config::get().getTitle()) :
			width(pWidth), height(pHeight), title(pTitle) {
			;
		}

		virtual ~Window() { glfwTerminate(); }

		void create(bool fullscreen = false);
		void setRenderMethod(void (*func)()) { loopCallback = func; }
		void open();
		void close();
		void exit() const { glfwTerminate(); }

		void setTitle(const std::string& t);
		void setSize(const unsigned& w, const unsigned& h);
		void setMode(const int& type, const int& value) { glfwWindowHint(type, value); }
		void setInputMode(const int& type, const int& value) { glfwSetInputMode(window, type, value); }
		void setEventResize(void (*func)(GLFWwindow*, int, int)) { glfwSetFramebufferSizeCallback(window, func); }
		void setEventKeyPress(void (*func)(GLFWwindow*, int, int, int, int)) { glfwSetKeyCallback(window, func); }
		void setEventInput(void (*func)(GLFWwindow*)) { inputCallback = func; }
		void setEventMouseMove(void (*func)(GLFWwindow*, double, double)) { glfwSetCursorPosCallback(window, func); }
		void setEventScroll(void (*func)(GLFWwindow*, double, double)) { glfwSetScrollCallback(window, func); }

		unsigned getWidth() const { return width; }
		unsigned getHeight() const { return height; }
		std::string getTitle() const { return title; }
		bool isCreate() const { return window != nullptr; }
	};
}
#endif
