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
	ConverterToNormalMap conventer;
	Scene* scene;
	Skybox skybox;
	Terrain terrain;
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

public:
	App(Window& win);
	virtual ~App();

	void render();
	void resize(const unsigned& width, const unsigned& height);
	void mouseMove(const double& posX, const double& posY);
	void mouseButton(GLFWwindow* win, int button, int action, int mods);
	void keyboardInput(GLFWwindow* win);
};
#endif
