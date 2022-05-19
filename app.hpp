#ifndef TERRAIN_APP_HPP
#define TERRAIN_APP_HPP 1

#include "include.hpp"

using namespace EngineSpace;

class App
{
	const unsigned TERRAIN_SIZE = 512;
	const unsigned PERLIN_MULTI = 1;

	Window& window;
	ShadersManager manager;
	Camera* camera;
	TextureGenerator2D generator;
	ConverterToNormalMap converter;
	Scene* scene;
	Skybox skybox;
	Terrain terrain;
	MousePicker* picker;
	Light pointLight;
	bool firstTime = true;
	bool polygonMode = false;
	float lastPosX = 0;
	float lastPosY = 0;

	void initShadersManager();
	void generateFlat();
	void generatePerlinPlain();
	void generatePerlinLowLands();
	void generatePerlinHighLands();
	void generatePerlinLittleMountains();
	void generatePerlinMountains();
	glm::vec3 calculateRay(double mouse_x, double mouse_y);
	void doShit(double x, double y, int button);

public:
	App(Window& win);
	virtual ~App();

	void render();
	void resize(const unsigned& width, const unsigned& height);
	void mouseMove(const double& posX, const double& posY);
	void scroll(const double& x, const double& y);
	void mouseButton(GLFWwindow* win, int button, int action, int mods);
	void keyboardInput(GLFWwindow* win);
};
#endif
