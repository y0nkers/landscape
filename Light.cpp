#include "Light.hpp"

namespace EngineSpace
{
	unsigned Light::amount = 0;

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
