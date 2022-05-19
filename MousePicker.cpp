// https://stackoverflow.com/questions/23975555/how-to-do-ray-plane-intersection
// https://stackoverflow.com/questions/59257678/intersect-a-ray-with-a-triangle-in-glsl-c
#include "MousePicker.hpp"

namespace EngineSpace 
{
	MousePicker::MousePicker(TextureGenerator2D* gen, ConverterToNormalMap* con, Terrain* ter) : generator(gen), converter(con), terrain(ter) {}

	glm::vec3 MousePicker::calculateRay(double mouse_x, double mouse_y, Window& window, Camera* camera)
	{
		// 3d normalised device coordinates. range [-1:1, -1:1, -1:1]
		float x = (2.0f * mouse_x) / window.getWidth() - 1.0f;
		float y = 1.0f - (2.0f * mouse_y) / window.getHeight();
		float z = -1.0f;
		glm::vec3 ray_nds = glm::vec3(x, y, z);

		// 4d Homogeneous Clip Coordinates. range [-1:1, -1:1, -1:1, -1:1]
		glm::vec4 ray_clip = glm::vec4(ray_nds.xyz, 1.0); // z point forward

		// 4d Eye (Camera) Coordinates. range [-x:x, -y:y, -z:z, -w:w]
		glm::vec4 ray_eye = glm::inverse(camera->getProjectionMatrix()) * ray_clip;
		ray_eye = glm::vec4(ray_eye.xy, -1.0, 0.0);

		// 4d World Coordinates. range [-x:x, -y:y, -z:z, -w:w]
		glm::vec3 ray_world = (glm::inverse(camera->getViewMatrix()) * ray_eye).xyz;
		// don't forget to normalise the vector at some point
		ray_world = glm::normalize(ray_world);

		std::cout << glm::to_string(ray_world) << std::endl;
		//std::cout << "cam " << glm::to_string(camera->getDirection()) << std::endl;
		return ray_world;
	}

	bool MousePicker::RayPlaneIntersection(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& plane_origin, const glm::vec3& plane_normal, float& distance)
	{
		float denominator = glm::dot(plane_normal, ray_direction);

		if (abs(denominator) >= 0.0001f) // 1e-6 = 0.000001
		{
			distance = glm::dot(plane_origin - ray_origin, plane_normal) / denominator;
			return (distance >= 0);
		}
		return false;
	}

	// Triangle

	bool MousePicker::PointInOrOn(glm::vec3 P1, glm::vec3 P2, glm::vec3 A, glm::vec3 B)
	{
		glm::vec3 CP1 = glm::cross(B - A, P1 - A);
		glm::vec3 CP2 = glm::cross(B - A, P2 - A);
		return glm::dot(CP1, CP2) >= 0;
	}

	bool MousePicker::PointInTriangle(glm::vec3 X, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
	{
		return
			PointInOrOn(X, point1, point2, point3) *
			PointInOrOn(X, point2, point3, point1) *
			PointInOrOn(X, point3, point1, point2);
	}

	glm::vec3 MousePicker::IntersectPlane(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3)
	{
		glm::vec3 N = glm::cross(point2 - point1, point3 - point1);
		glm::vec3 X = ray_origin + ray_direction * glm::dot(point1 - ray_origin, N) / glm::dot(ray_direction, N);
		return X;
	}

	bool MousePicker::IntersectTriangle(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3)
	{
		glm::vec3 X = IntersectPlane(ray_origin, ray_direction, point1, point2, point3);
		return PointInTriangle(X, point1, point2, point3);
	}

	void MousePicker::doGlobalShit(const glm::vec3& camera_position, const glm::vec3& ray_direction, const unsigned& width, const unsigned& height, float& distance, const int& mode)
	{
		std::vector<GLubyte> points = generator->getTextureData();
		std::vector<GLubyte> normals = converter->getNormalMap();

		unsigned size = width * height * 4;
		for (unsigned index = 4; index < size - 8; index += 4)
		{
			glm::vec3 point1 = glm::vec3(points[index - 4], points[index - 3], points[index - 2]);
			glm::vec3 point2 = glm::vec3(points[index], points[index + 1], points[index + 2]);
			glm::vec3 point3 = glm::vec3(points[index + 4], points[index + 5], points[index + 6]);

			bool intersection = IntersectTriangle(camera_position, ray_direction, point1, point2, point3);
			if (intersection)
			{
				int height = 10 + (rand() % static_cast<int>(20 - 10 + 1));
				if (mode == GLFW_MOUSE_BUTTON_RIGHT) height = -height;
				generator->changePointHeight(index, 100);
			}
		}

		//for (unsigned w = 0; w < width; ++w)
		//{
		//	for (unsigned h = 0; h < height; ++h)
		//	{
		//		unsigned index = (w * width + h) * 4;
		//		glm::vec3 point = glm::vec3(points[index], points[index + 1], points[index + 2]);
		//		glm::vec3 normal = glm::vec3(normals[index], normals[index + 1], normals[index + 2]);
		//		bool intersection = RayPlaneIntersection(camera_position, ray_direction, point, normal, distance);
		//		//if (intersection)
		//		//{
		//			int height = 10 + (rand() % static_cast<int>(20 - 10 + 1));
		//			if (mode == GLFW_MOUSE_BUTTON_RIGHT) height = -height;
		//			generator->changePointHeight(index, height);
		//		//}
		//	}
		//}
		generator->bindTexture(terrain->getHeightMap(), width, height, width * height * 4);
		converter->convert(generator->getTextureData(), terrain->getNormalMap(), width, height);
	}
}