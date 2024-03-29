﻿#ifndef CONFIG_HPP
#define CONFIG_HPP 1
#define DEBUG_ENGINE 0 // Engine errors
#define GLM_FORCE_SWIZZLE

#include "Singleton.hpp"
#include "json.hpp"
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

using json = nlohmann::json; // json reader

namespace EngineSpace
{
	class Config : public Singleton<Config>
	{
		friend class Singleton<Config>;

		std::string title = "Terrain Generator";
		unsigned majorVersion = 4;
		unsigned minorVersion = 1;
		unsigned windowWidth = 1280;
		unsigned windowHeight = 1024;
		unsigned samples = 8; // Количество сэмплов для MSAA сглаживания
		float cameraPitch = -30;
		float cameraYaw = -180;
		float cameraSpeed = 0.5;
		float cameraSensitivity = 0.1;
		float cameraFov = 45;
		float cameraFar = 1000;
		float cameraNear = 0.01;
		float anisotropy = 8; // степень анизотропной фильтрации
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);

		Config() {
			std::ifstream i("config.json");
			json json;
			i >> json;
			i.close();

			windowWidth = json["windowWidth"];
			windowHeight = json["windowHeight"];
			samples = json["samples"];
			cameraPitch = json["cameraPitch"];
			cameraYaw = json["cameraYaw"];
			cameraSpeed = json["cameraSpeed"];
			cameraSensitivity = json["cameraSensitivity"];
			cameraFov = json["cameraFov"];
			cameraFar = json["cameraFar"];
			cameraNear = json["cameraNear"];
			anisotropy = json["anisotropy"];
		}

	public:
		std::string getTitle() const { return title; }
		unsigned getWindowWidth() const { return windowWidth; }
		unsigned getWindowHeight() const { return windowHeight; }
		unsigned getMajorVersion() const { return majorVersion; }
		unsigned getMinorVersion() const { return minorVersion; }
		unsigned getSamples() const { return samples; }
		float getCameraPitch() const { return cameraPitch; }
		float getCameraYaw() const { return cameraYaw; }
		float getCameraSpeed() const { return cameraSpeed; }
		float getCameraSensitivity() const { return cameraSensitivity; }
		float getCameraFov() const { return cameraFov; }
		float getCameraFar() const { return cameraFar; }
		float getCameraNear() const { return cameraNear; }
		glm::vec3 getCameraPosition() const { return cameraPosition; }
		glm::vec3 getCameraDirection() const { return cameraDirection; }
		float getAnisotropy() const { return anisotropy; }
	};
}
#endif
