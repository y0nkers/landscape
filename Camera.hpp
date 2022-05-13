#ifndef CAMERA_HPP
#define CAMERA_HPP 1

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.hpp"

namespace EngineSpace
{
	class Camera
	{
		glm::vec3 position; // Вектор позиции камеры
		glm::vec3 direction; // Вектор куда смотрит камера
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Где находится верх у камеры
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f); // Вверх мировой
		glm::vec3 right;
		float pitch; // угол наклона вперёд/назад
		float yaw; // поворот влево/вправо в горизонтальной плоскости
		float speed;
		float sensitivity; // Чувствительность к повороту
		float fov;
		float far;
		float near;
		bool speedUp = false;

	protected:
		Window& window;

	public:
		Camera
		(	Window& win,
			const glm::vec3& pPosition = Config::get().getCameraPosition(),
			const glm::vec3& pDirection = Config::get().getCameraDirection(),
			const float& pPitch = Config::get().getCameraPitch(),
			const float& pYaw = Config::get().getCameraYaw(),
			const float& pSpeed = Config::get().getCameraSpeed(),
			const float& pSensitivity = Config::get().getCameraSensitivity(),
			const float& pFov = Config::get().getCameraFov(),
			const float& pNear = Config::get().getCameraNear(),
			const float& pFar = Config::get().getCameraFar()
		) :
			window(win), position(pPosition), direction(pDirection),
			pitch(pPitch), yaw(pYaw), speed(pSpeed), sensitivity(pSensitivity),
			fov(pFov), near(pNear), far(pFar)
		{ updateVectors(); }

		// functionality
		void moveTop();
		void moveBottom();
		void moveRight();
		void moveLeft();
		void changeFOV(const double& value);
		void updateVectors();
		void rotate(const float& offsetX, const float& offsetY);

		// setters
		void toggleSpeedUp() { speedUp = !speedUp; }
		void setPosition(const glm::vec3& vec) { position = vec; }
		void setDirection(const glm::vec3& vec) { direction = vec; }
		void setPitch(const float& val) { pitch = val; }
		void setYaw(const float& val) { yaw = val; }
		void setSpeed(const float& val) { speed = val; }
		void setFov(const float& val) { fov = val; }
		void setFar(const float& val) { far = val; }
		void setNear(const float& val) { near = val; }
		void setSensitivity(const float& val) { sensitivity = val; }

		// getters
		glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + direction, up); } // Матрица взгляда
		glm::mat4 getProjectionMatrix() const { return glm::perspective(glm::radians(getFov()), (float)window.getWidth() / (float)window.getHeight(), getNear(), getFar()); } // Матрица перспективы
		glm::mat4 getViewProjectionMatrix() const { return getProjectionMatrix() * getViewMatrix(); }
		glm::vec3 getPosition() const { return position; }
		glm::vec3 getDirection() const { return direction; }
		float getPitch() const { return pitch; }
		float getYaw() const { return yaw; }
		float getSpeed() const { return speed; }
		float getFov() const { return fov; }
		float getNear() const { return near; }
		float getFar() const { return far; }
		bool isSpeedUp() const { return speedUp; }
	};
}
#endif