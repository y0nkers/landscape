#include "Light.hpp"

namespace EngineSpace
{
	unsigned Light::amount = 0;

	void Light::generateShadowTransforms()
	{
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, Config::get().getShadowFar());
		shadowTransforms.clear();
		shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	}

	void Light::render(Program& program)
	{
		std::string prefix = "lights[" + std::to_string(getIndex()) + "]";
		program.setVec3(std::string(prefix + ".position").c_str(), position);
		program.setVec3(std::string(prefix + ".ambient").c_str(), ambient);
		program.setVec3(std::string(prefix + ".diffuse").c_str(), diffuse);
		program.setVec3(std::string(prefix + ".specular").c_str(), specular);
		program.setFloat(std::string(prefix + ".constant").c_str(), constant);
		program.setFloat(std::string(prefix + ".linear").c_str(), linear);
		program.setFloat(std::string(prefix + ".quadratic").c_str(), quadratic);
	}
}
