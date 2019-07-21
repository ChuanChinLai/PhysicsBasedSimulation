#pragma once

#include <glm/vec3.hpp>

namespace LaiEngine
{
	namespace Physics
	{
		class Ray
		{
		public:

			Ray();
			Ray(const glm::vec3& newOrigin, const glm::vec3& newDirection);
			Ray(const Ray& other);

			glm::vec3 PointAt(const float t) const;

			glm::vec3 Origin; 
			glm::vec3 Direction;
		};
	}
}

#include "Ray_inline.h"