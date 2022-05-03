#include "app.hpp"

App::App(Window& win) :
	window(win), perspectiveCamera(win), camera(&perspectiveCamera),
	//bloomEffect(win), post(win), postHDR(win, 2), water(win, camera),
	//fontRenderer(win, Font("fonts/arial.ttf")),
	pointLight(glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(2.0f), glm::vec3(2.1f), glm::vec3(1.0f), 1.0f, 0.0f, 0.0f)
{
	initShadersManager();

	camera->setPosition(glm::vec3(0.0f, 25.0f, 0.0f));
	camera->rotate(50, -80);

	//fontRenderer.setColor(glm::vec3(1.0));
	skybox.getTexture().load({ "textures/skybox/right.jpg", "textures/skybox/left.jpg", "textures/skybox/top.jpg", "textures/skybox/bottom.jpg", "textures/skybox/front.jpg", "textures/skybox/back.jpg" });

	terrain.getGrassTexture().load("textures/grass.jpg", GL_TEXTURE_2D);
	terrain.getStoneTexture().load("textures/stone.jpg", GL_TEXTURE_2D);
	terrain.setPosition(glm::vec3(0.0f));
	terrain.scale(glm::vec3(400.0f));

	//water.getDudvMap().load("textures/water-dudv.jpg", GL_TEXTURE_2D);
	//water.getNormalMap().load("textures/water-normal.jpg", GL_TEXTURE_2D);
	//water.setPosition(glm::vec3(0.0f, 15.0f, 0.0f));
	//water.scale(glm::vec3(200.0f));

	scene = new Scene(window, camera, manager);
	scene->addSkybox(skybox);
	scene->addTerrain(terrain);
	scene->addLight(pointLight);

	generatePerlinPlain();
}

void App::initShadersManager()
{
	Shader terrainVertex = Shader::createVertexShader("shaders/terrain/terrain.vert");
	Shader terrainTessControl = Shader::createTessalationControlShader("shaders/terrain/terrain_control.glsl");

	/*Program depthTerrainProgram;
	depthTerrainProgram.create();
	depthTerrainProgram.attachShader(terrainVertex);
	depthTerrainProgram.attachShader(terrainTessControl);
	depthTerrainProgram.attachShader(Shader::createTessalationEvaluationShader("shaders/depth/terrain_eval_depth.glsl"));
	depthTerrainProgram.attachShader(Shader::createGeometryShader("shaders/depth/depth.gs"));
	depthTerrainProgram.attachShader(Shader::createFragmentShader("shaders/depth/depth.fs"));
	depthTerrainProgram.link();*/

	Program terrainProgram;
	terrainProgram.create();
	terrainProgram.attachShader(terrainVertex);
	terrainProgram.attachShader(terrainTessControl);
	terrainProgram.attachShader(Shader::createTessalationEvaluationShader("shaders/terrain/terrain_eval.glsl"));
	terrainProgram.attachShader(Shader::createFragmentShader("shaders/terrain/terrain.frag"));
	terrainProgram.link();

	manager.setSkyboxProgram(Program("shaders/skybox/skybox.vert", "shaders/skybox/skybox.frag"));
	//manager.setHDRProgram(Program("shaders/effect/hdr.vs", "shaders/effect/hdr.fs"));
	//manager.setBlurProgram(Program("shaders/effect/blur.vs", "shaders/effect/blur.fs"));
	//manager.setFontProgram(Program("shaders/font/font.vs", "shaders/font/font.fs"));
	//manager.setPostProcessProgram(Program("shaders/effect/postprocessing.vs", "shaders/effect/postprocessing.fs"));
	//manager.setWaterProgram(Program("shaders/water/water.vs", "shaders/water/water.fs"));
	manager.setTerrainProgram(terrainProgram);
	//manager.setTerrainDepthProgram(depthTerrainProgram);
}

App::~App() { delete scene; }

void App::render()
{
	EngineSpace::Engine::get().initDeltaTime();
	EngineSpace::Engine::get().calcFPS();

	// scene->renderShadows();

	// if (isWater) water.renderReflectAndRefract(scene);

	//if (!polygonMode) postHDR.startProcessing();

	/*if (isWater)
	{
		scene->addWater(water);
		scene->render();
		scene->removeWater(0);
	}
	else*/ scene->render(polygonMode);

	/*if (!polygonMode)
	{
		postHDR.endProcessing();
		bloomEffect.blurTexture(manager.getBlurProgram(), postHDR.getResultTextures()[1]);

		std::vector<Texture> result;
		result.push_back(postHDR.getResultTextures()[0]);
		result.push_back(bloomEffect.getResultTexture());

		post.startProcessing();
		PostProcessing::renderToQuad(manager.getHDRProgram(), result);

		fontRenderer.setScale(0.5);
		fontRenderer.setPosition(8, window.getHeight() - 30);
		fontRenderer.setText(EngineSpace::Engine::get().getFPS());
		fontRenderer.render(manager.getFontProgram());

		fontRenderer.setScale(0.3);
		fontRenderer.setPosition(window.getWidth() - 143, window.getHeight() - 15);
		fontRenderer.setText("Tessellation Level: " + std::to_string(terrain.getTessLevel()));
		fontRenderer.render(manager.getFontProgram());
		post.endProcessing();
		Program& prog = manager.getPostProcessProgram();
		PostProcessing::renderToQuad(prog, post.getResultTextures());
	}*/
}

void App::resize(const unsigned& width, const unsigned& height)
{
	window.setSize(width, height);
	//bloomEffect.updateBuffers();
	//postHDR.updateBuffers();
	//post.updateBuffers();
	//water.buffers.updateBuffers();
}

void App::mouseMove(const double& posX, const double& posY)
{
	if (firstTime)
	{
		lastPosX = posX;
		lastPosY = posY;
		firstTime = false;
	}
	camera->rotate(posX - lastPosX, lastPosY - posY);
	lastPosX = posX;
	lastPosY = posY;
}

void App::keyboardInput(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.close();
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveTop();
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveBottom();
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveLeft();
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRight();
	if (!camera->isSpeedUp() && glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { camera->setSpeed(camera->getSpeed() * 5); camera->toggleSpeedUp(); }
	else if (camera->isSpeedUp() && glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) { camera->setSpeed(camera->getSpeed() / 5); camera->toggleSpeedUp(); }

	if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS) {
		polygonMode = !polygonMode;
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_LINE : GL_FILL);
	}

	if (glfwGetKey(win, GLFW_KEY_N) == GLFW_PRESS)
	{
		isWater = false;
	}
	else if (glfwGetKey(win, GLFW_KEY_M) == GLFW_PRESS)
	{
		isWater = true;
	}

	if (glfwGetKey(win, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		terrain.setDepth(terrain.getDepth() - 0.001);
		//water.setPosition(glm::vec3(0.0f, water.getPosition().y - terrain.getDepth(), 0.0f));
	}
	else if (glfwGetKey(win, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		terrain.setDepth(terrain.getDepth() + 0.001);
		//water.setPosition(glm::vec3(0.0f, water.getPosition().y + terrain.getDepth(), 0.0f));
	}

	if (glfwGetKey(win, GLFW_KEY_T) == GLFW_PRESS)
	{
		if (terrain.getTessLevel() > 1)
			terrain.setTessLevel(terrain.getTessLevel() - 1);
	}
	else if (glfwGetKey(win, GLFW_KEY_Y) == GLFW_PRESS)
	{
		if (terrain.getTessLevel() < 64)
			terrain.setTessLevel(terrain.getTessLevel() + 1);
	}

	if (glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS)
		scene->setShadows(true);
	else if (glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
		scene->setShadows(false);

	if (glfwGetKey(win, GLFW_KEY_1) == GLFW_PRESS)
		generatePerlinPlain();
	else if (glfwGetKey(win, GLFW_KEY_2) == GLFW_PRESS)
		generatePerlinLowLands();
	else if (glfwGetKey(win, GLFW_KEY_3) == GLFW_PRESS)
		generatePerlinHighLands();
	else if (glfwGetKey(win, GLFW_KEY_4) == GLFW_PRESS)
		generatePerlinLittleMountains();
	else if (glfwGetKey(win, GLFW_KEY_5) == GLFW_PRESS)
		generatePerlinMountains();

	//else if (glfwGetKey(win, GLFW_KEY_6) == GLFW_PRESS)
	//    generateSmooth256();
	//else if (glfwGetKey(win, GLFW_KEY_7) == GLFW_PRESS)
	//    generateSmooth128();
	//else if (glfwGetKey(win, GLFW_KEY_8) == GLFW_PRESS)
	//    generateSmooth64();
	//else if (glfwGetKey(win, GLFW_KEY_9) == GLFW_PRESS)
	//    generateSmooth32();
	//else if (glfwGetKey(win, GLFW_KEY_0) == GLFW_PRESS)
	//    generateSmooth16();
}

void App::generatePerlinPlain()
{
	static const float FREQUENT = 2;
	static const float AMPLITUDE = 2;
	static const float PERSISTENCE = 1;
	static const unsigned OCTAVES = 1;
	static unsigned offset = 1;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENT, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinLowLands()
{
	static const float FREQUENT = 3;
	static const float AMPLITUDE = 3;
	static const float PERSISTENCE = 2;
	static const unsigned OCTAVES = 2;
	static unsigned offset = 1;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENT, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinHighLands()
{
	static const float FREQUENT = 4;
	static const float AMPLITUDE = 4.5;
	static const float PERSISTENCE = 2.5;
	static const unsigned OCTAVES = 3;
	static unsigned offset = 1;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENT, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinLittleMountains()
{
	static const float FREQUENT = 10;
	static const float AMPLITUDE = 20;
	static const float PERSISTENCE = 0.5;
	static const unsigned OCTAVES = 5;
	static unsigned offset = 1;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENT, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinMountains()
{
	static const float FREQUENT = 20;
	static const float AMPLITUDE = 40;
	static const float PERSISTENCE = 0.45;
	static const unsigned OCTAVES = 6;
	static unsigned offset = 1;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENT, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

//void App::generateSmooth256()
//{
//    generator.generate(terrain.getHeightMap(), SmoothNoise2D(256), TERRAIN_SIZE, TERRAIN_SIZE);
//    conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
//}
//
//void App::generateSmooth128()
//{
//    generator.generate(terrain.getHeightMap(), SmoothNoise2D(128), TERRAIN_SIZE, TERRAIN_SIZE);
//    conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
//}
//
//void App::generateSmooth64()
//{
//    generator.generate(terrain.getHeightMap(), SmoothNoise2D(64), TERRAIN_SIZE, TERRAIN_SIZE);
//    conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
//}
//
//void App::generateSmooth32()
//{
//    generator.generate(terrain.getHeightMap(), SmoothNoise2D(32), TERRAIN_SIZE, TERRAIN_SIZE);
//    conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
//}
//
//void App::generateSmooth16()
//{
//    generator.generate(terrain.getHeightMap(), SmoothNoise2D(16), TERRAIN_SIZE, TERRAIN_SIZE);
//    conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
//}
