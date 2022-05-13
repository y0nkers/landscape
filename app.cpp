#include "app.hpp"

App::App(Window& win) :
	window(win), 
	pointLight(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(2.0f), glm::vec3(2.1f), glm::vec3(1.0f), 1.0f, 0.0f, 0.0f)
{
	initShadersManager();

	camera = new Camera(win);
	camera->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	skybox.getTexture().load({ "textures/skybox/right.jpg", "textures/skybox/left.jpg", "textures/skybox/top.jpg", "textures/skybox/bottom.jpg", "textures/skybox/front.jpg", "textures/skybox/back.jpg" });

	terrain.getGrassTexture().load("textures/grass.jpg", GL_TEXTURE_2D);
	terrain.getStoneTexture().load("textures/stone.jpg", GL_TEXTURE_2D);
	terrain.setPosition(glm::vec3(0.0f));
	terrain.setScale(glm::vec3(1.0f));

	scene = new Scene(window, camera, manager);
	scene->addSkybox(skybox);
	scene->addTerrain(terrain);
	scene->addLight(pointLight);

	generateFlat();
}

void App::initShadersManager()
{
	Shader terrainVertex = Shader::createVertexShader("shaders/terrain/terrain.vert");
	Shader terrainTessControl = Shader::createTessalationControlShader("shaders/terrain/terrain_control.glsl");

	Program terrainProgram;
	terrainProgram.create();
	terrainProgram.attachShader(terrainVertex);
	terrainProgram.attachShader(terrainTessControl);
	terrainProgram.attachShader(Shader::createTessalationEvaluationShader("shaders/terrain/terrain_eval.glsl"));
	terrainProgram.attachShader(Shader::createFragmentShader("shaders/terrain/terrain.frag"));
	terrainProgram.link();

	manager.setSkyboxProgram(Program("shaders/skybox/skybox.vert", "shaders/skybox/skybox.frag"));
	manager.setTerrainProgram(terrainProgram);
}

App::~App() { delete camera; delete scene; }

void App::render()
{
	EngineSpace::Engine::get().initDeltaTime();
	EngineSpace::Engine::get().calcFPS();

	scene->render(polygonMode);
}

void App::resize(const unsigned& width, const unsigned& height)
{
	window.setSize(width, height);
}

void App::mouseMove(const double& posX, const double& posY)
{
	if (firstTime)
	{
		lastPosX = posX;
		lastPosY = posY;
		firstTime = false;
	}
	if (window.getInputMode(GLFW_CURSOR) == GLFW_CURSOR_DISABLED) camera->rotate(posX - lastPosX, lastPosY - posY);
	lastPosX = posX;
	lastPosY = posY;
	// std::cout << "Mouse position: x = " << lastPosX << ", y = " << lastPosY << std::endl;
}

void App::scroll(const double& x, const double& y) {
	camera->changeFOV(y);
}

void App::mouseButton(GLFWwindow* win, int button, int action, int mods)
{
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_REPEAT)
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double xpos = 0, ypos = 0;
		glfwGetCursorPos(win, &xpos, &ypos);
		//static double x = xpos, y = ypos;
		std::cout << "Mouse button pressed." << std::endl;

		std::cout << "Cursor Position at (" << xpos << ";" << ypos << ")" << std::endl;
		terrain.toggleClick();
		terrain.setClickPoint(calculateRay(xpos, ypos));
	}
	else if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		terrain.toggleClick();
		terrain.setClickPoint(glm::vec3(0.0f));
		std::cout << "Mouse button released." << std::endl;
	}
}

glm::vec3 App::calculateRay(double mouse_x, double mouse_y)
{
	// 3d normalised device coordinates. range [-1:1, -1:1, -1:1]
	float x = (2.0f * mouse_x) / window.getWidth() - 1.0f;
	float y = 1.0f - (2.0f * mouse_y) / window.getHeight();
	float z = 1.0f;
	glm::vec3 ray_nds = glm::vec3(x, y, z);

	// 4d Homogeneous Clip Coordinates. range [-1:1, -1:1, -1:1, -1:1]
	glm::vec4 ray_clip = glm::vec4(ray_nds.xy, -1.0, 1.0); // z point forward

	// 4d Eye (Camera) Coordinates. range [-x:x, -y:y, -z:z, -w:w]
	glm::vec4 ray_eye = glm::inverse(camera->getProjectionMatrix()) * ray_clip;
	ray_eye = glm::vec4(ray_eye.xy, -1.0, 0.0);

	// 4d World Coordinates. range [-x:x, -y:y, -z:z, -w:w]
	glm::vec3 ray_world = (glm::inverse(camera->getViewMatrix()) * ray_eye).xyz;
	// don't forget to normalise the vector at some point
	ray_world = glm::normalize(ray_world);
	std::cout << glm::to_string(ray_world) << std::endl;
	//std::cout << ray_world.x << std::endl << ray_world.y << std::endl << ray_world.z << std::endl;
	return ray_world;
}

void App::keyboardInput(GLFWwindow* win)
{
	// Close window - ESC
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) window.close(); 

	// Camera control - WASD + Shift
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) camera->moveTop();
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) camera->moveLeft();
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) camera->moveBottom();
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) camera->moveRight();
	if (!camera->isSpeedUp() && glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { camera->setSpeed(camera->getSpeed() * 4); camera->toggleSpeedUp(); }
	else if (camera->isSpeedUp() && glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) { camera->setSpeed(camera->getSpeed() / 4); camera->toggleSpeedUp(); }

	// Change camera mode - C
	if (glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS)
		window.setInputMode(GLFW_CURSOR, window.getInputMode(GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

	// Polygon Mode - Space
	if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS) {
		polygonMode = !polygonMode;
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_LINE : GL_FILL);
	}
	
	// Terrain depth (+/-) =/-
	if (glfwGetKey(win, GLFW_KEY_EQUAL) == GLFW_PRESS) terrain.setDepth(terrain.getDepth() + 0.001);
	else if (glfwGetKey(win, GLFW_KEY_MINUS) == GLFW_PRESS)	/*if (terrain.getDepth() > 0)*/ terrain.setDepth(terrain.getDepth() - 0.001);

	// Tesselation level(+/-) T/Y
	if (glfwGetKey(win, GLFW_KEY_T) == GLFW_PRESS)
	{
		if (terrain.getTessLevel() < 64) terrain.setTessLevel(terrain.getTessLevel() + 1);
	}
	else if (glfwGetKey(win, GLFW_KEY_Y) == GLFW_PRESS)
	{
		if (terrain.getTessLevel() > 1) terrain.setTessLevel(terrain.getTessLevel() - 1);
	}

	// Generate different terrains
	if (glfwGetKey(win, GLFW_KEY_1) == GLFW_PRESS)		generatePerlinPlain();
	else if (glfwGetKey(win, GLFW_KEY_2) == GLFW_PRESS) generatePerlinLowLands();
	else if (glfwGetKey(win, GLFW_KEY_3) == GLFW_PRESS) generatePerlinHighLands();
	else if (glfwGetKey(win, GLFW_KEY_4) == GLFW_PRESS) generatePerlinLittleMountains();
	else if (glfwGetKey(win, GLFW_KEY_5) == GLFW_PRESS) generatePerlinMountains();
}

void App::generateFlat() 
{
	static const float FREQUENCY = 1;
	static const float AMPLITUDE = 0;
	static const float PERSISTENCE = 1;
	static const unsigned OCTAVES = 1;
	static unsigned offset = 0;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENCY, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinPlain() 
{
	static const float FREQUENT = 2;
	static const float AMPLITUDE = 2;
	static const float PERSISTENCE = 1;
	static const unsigned OCTAVES = 1;
	static unsigned offset = 0;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENT, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinLowLands()
{
	static const float FREQUENCY = 3;
	static const float AMPLITUDE = 3;
	static const float PERSISTENCE = 2;
	static const unsigned OCTAVES = 2;
	static unsigned offset = 0;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENCY, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinHighLands()
{
	static const float FREQUENCY = 4;
	static const float AMPLITUDE = 4.5;
	static const float PERSISTENCE = 2.5;
	static const unsigned OCTAVES = 3;
	static unsigned offset = 0;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENCY, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinLittleMountains()
{
	static const float FREQUENCY = 10;
	static const float AMPLITUDE = 20;
	static const float PERSISTENCE = 0.5;
	static const unsigned OCTAVES = 5;
	static unsigned offset = 0;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENCY, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}

void App::generatePerlinMountains() 
{
	static const float FREQUENCY = 20;
	static const float AMPLITUDE = 40;
	static const float PERSISTENCE = 0.45;
	static const unsigned OCTAVES = 6;
	static unsigned offset = 0;
	++offset;

	generator.generate(terrain.getHeightMap(), PerlinNoise2D(FREQUENCY, AMPLITUDE, PERSISTENCE, OCTAVES, PERLIN_MULTI, offset, offset), TERRAIN_SIZE, TERRAIN_SIZE);
	conventer.convert(generator.getTextureData(), terrain.getNormalMap(), TERRAIN_SIZE, TERRAIN_SIZE);
}
