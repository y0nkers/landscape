#ifndef MOUSE_PICKER_HPP
#define MOUSE_PICKER_HPP 1

#include "include.hpp"

namespace EngineSpace
{
	class MousePicker
	{
		TextureGenerator2D* generator;
		ConverterToNormalMap* converter;
		Terrain* terrain;

	public:
		MousePicker(TextureGenerator2D*, ConverterToNormalMap*, Terrain*);
		glm::vec3 calculateRay(double mouse_x, double mouse_y, Window& window, Camera* camera);
		bool RayPlaneIntersection(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& plane_origin, const glm::vec3& plane_normal, float& distance);

		bool PointInOrOn(glm::vec3 P1, glm::vec3 P2, glm::vec3 A, glm::vec3 B);
		bool PointInTriangle(glm::vec3 x, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
		glm::vec3 IntersectPlane(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
		bool IntersectTriangle(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
		void doGlobalShit(const glm::vec3& camera_position, const glm::vec3& ray_direction, const unsigned& width, const unsigned& height, float& distance, const int& mode);
	};
}
#endif
