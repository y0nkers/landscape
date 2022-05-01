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
	InterfaceCamera* camera;
	PerspectiveCamera perspectiveCamera;
	//FontRenderer fontRenderer;
	TextureGenerator2D generator;
	ConverterToNormalMap conventer;
	//Bloom bloomEffect;
	//PostProcessing postHDR;
	//PostProcessing post;
	Scene* scene;
	//Skybox skybox;
	Terrain terrain;
	//Water water;
	//Light pointLight;
	bool firstTime = true;
	bool polygonMode = false;
	float lastPosX = 0;
	float lastPosY = 0;
	bool isWater = true;

	void initShadersManager();
	void generatePerlinPlain();
	void generatePerlinLowLands();
	void generatePerlinHighLands();
	void generatePerlinLittleMountains();
	void generatePerlinMountains();
	/*void generateSmooth256();
	void generateSmooth128();
	void generateSmooth64();
	void generateSmooth32();
	void generateSmooth16();*/

public:
	App(Window& win);
	virtual ~App();

	void render();
	void resize(const unsigned& width, const unsigned& height);
	void mouseMove(const double& posX, const double& posY);
	void keyboardInput(GLFWwindow* win);
};
#endif
