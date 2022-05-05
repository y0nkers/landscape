#ifndef SCENE_HPP
#define SCENE_HPP 1

#include <vector>
#include "Skybox.hpp"
#include "Terrain.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "Light.hpp"
#include "ShadersManager.hpp"

namespace EngineSpace
{
	class Scene
	{
		Window& window;
		ShadersManager& manager;
		Camera* camera = nullptr;
		Skybox* skybox = nullptr;
		std::vector<Renderable*> terrains;
		std::vector<Light*> lights;

		void initProgram(Program& program, const glm::vec4& clipPlane);
		void initPrograms(const glm::vec4& clipPlane);

		void renderTerrains(Program& prog);
		void renderLights();
		void renderSkybox(bool polygonMode);

	public:
		Scene(Window& win, Camera* cam, ShadersManager& shadersmanager) : window(win), camera(cam), manager(shadersmanager) { ; }

		virtual void render(bool polygonMode, const glm::vec4& clipPlane = glm::vec4(0, 1, 0, 10000));

		void addSkybox(Skybox& obj) { skybox = &obj; }
		void addLight(Light& obj);
		void addTerrain(Renderable& obj) { terrains.push_back(&obj); }


		void removeLight(const unsigned& n);
		void removeTerrain(const unsigned& n) { terrains.erase(terrains.begin() + n); }

		Skybox& getSkybox() { return *skybox; }
		std::vector<Renderable*>& getTerrains() { return terrains; }
		std::vector<Light*>& getLights() { return lights; }
	};
}
#endif
