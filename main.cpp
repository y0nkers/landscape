#include <cstdlib>
#include <ctime>
#include "app.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Window* window = nullptr;
App* editor = nullptr;

void loop() { editor->render(); }
void resizeEvent(GLFWwindow* win, int w, int h) { editor->resize(w, h); }
void mouseMoveEvent(GLFWwindow* win, double posX, double posY) { editor->mouseMove(posX, posY); }
void mouseButtonEvent(GLFWwindow* win, int button, int action, int mods) { editor->mouseButton(win, button, action, mods); }
void processInput(GLFWwindow* win) { editor->keyboardInput(win); }
void onScroll(GLFWwindow* win, double x, double y) { editor->scroll(x, y); }

int main()
{
	srand((unsigned)time(NULL));
	try
	{
		bool isFullScreen = false;
		window = new Window;
		window->create(isFullScreen);
		window->setTitle("Terrain Generator");
		editor = new App(*window);
		window->setRenderMethod(loop);
		window->setEventResize(resizeEvent);
		window->setEventInput(processInput);
		window->setEventMouseMove(mouseMoveEvent);
		window->setEventMouseButton(mouseButtonEvent);
		window->setEventScroll(onScroll);
		window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		window->open();

		delete editor;
		delete window;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		std::cin.get();
	}
	return 0;
}
