#include "Scene.hpp"

namespace EngineSpace
{
	void Scene::initPrograms(const glm::vec4& clipPlane)
	{
		initProgram(manager.getTerrainProgram(), clipPlane);
	}

	void Scene::initProgram(Program& program, const glm::vec4& clipPlane)
	{
		if (program.getId() != 0)
		{
			program.use();
			program.setMat4("viewProject", camera->getViewProjectionMatrix());
			program.setVec3("viewPos", camera->getPosition());
			program.setInt("lightsAmount", Light::amount);
			program.setInt("allowShadows", allowShadows ? 1 : 0);
			program.setVec4("clipPlane", clipPlane);
		}
	}

	void Scene::render(bool polygonMode, const glm::vec4& clipPlane)
	{
		glViewport(0, 0, window.getWidth(), window.getHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		initPrograms(clipPlane);
		renderLights();
		renderTerrains(manager.getTerrainProgram());
		renderSkybox(polygonMode);
	}

	void Scene::renderTerrains(Program& prog)
	{
		if (prog.getId() != 0)
		{
			prog.use();
			for (unsigned i = 0; i < terrains.size(); ++i)
				terrains[i]->render(prog);
		}
	}

	void Scene::renderSkybox(bool polygonMode)
	{
		Program& skyboxProgram = manager.getSkyboxProgram();
		if (skybox != nullptr && skyboxProgram.getId() != 0)
		{
			skyboxProgram.use();
			glm::mat4 vp = camera->getProjectionMatrix() * glm::mat4(glm::mat3(camera->getViewMatrix()));
			skyboxProgram.setMat4("viewProject", vp);
			skyboxProgram.setBool("polygonMode", polygonMode);
			skybox->render(skyboxProgram);
		}
	}

	void Scene::renderLights()
	{
		Program& worldProgram = manager.getTerrainProgram();
		bool isWorldProgram = worldProgram.getId() != 0;

		for (unsigned i = 0; i < lights.size(); ++i)
		{
			if (isWorldProgram)
			{
				worldProgram.use();
				lights[i]->render(worldProgram);
			}
		}
	}

	void Scene::addLight(Light& obj)
	{
		lights.push_back(&obj);
	}

	void Scene::removeLight(const unsigned& n)
	{
		lights.erase(lights.begin() + n);
	}
}
