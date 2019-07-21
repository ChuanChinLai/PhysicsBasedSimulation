#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <tuple>

namespace LaiEngine
{
	namespace Math
	{
		std::tuple<glm::vec3, glm::vec3> GetTangential(const glm::vec3& v);

		glm::vec3 GetuniformSampleCone(float u1, float u2, const glm::vec3& axis, float angle);

		float Random(); 
	}
}