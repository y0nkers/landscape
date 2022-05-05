#ifndef TRANSFORMATIONABLE_HPP
#define TRANSFORMATIONABLE_HPP 1

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderable.hpp"

namespace EngineSpace
{
	class Transformationable : public Renderable
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::mat4 rotation = glm::mat4(1.0f);
		glm::vec3 scale = glm::vec3(1.0f);

	public:
		virtual void render(Program& program)
		{
			program.setMat4("model", getTransformMatrix());
		}
		virtual ~Transformationable() {}

		glm::mat4 getTransformMatrix() const
		{
			glm::mat4 matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix, position);
			matrix = glm::scale(matrix, scale);
			matrix = matrix * rotation;
			return matrix;
		}

		void rotate(const float& angle, const glm::vec3& vec) { rotation = glm::rotate(rotation, glm::radians(angle), vec); }
		void rotateX(const float& angle) { rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f)); }
		void rotateY(const float& angle) { rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)); }
		void rotateZ(const float& angle) { rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f)); }
		void translate(const glm::vec3& translate) { position += translate; }
		void setScale(const glm::vec3& vec) { scale = vec; }

		void setPosition(const glm::vec3& vec) { position = vec; }
		glm::vec3 getPosition() const { return position; }
		glm::vec3 getScale() const { return scale; }
		glm::mat4 getRotation() const { return rotation; }
	};
}
#endif
