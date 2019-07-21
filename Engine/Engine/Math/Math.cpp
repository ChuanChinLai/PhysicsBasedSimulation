#include "Math.h"

#include <Engine/Utility/Constants.h>

#include <algorithm>
#include <random>

std::tuple<glm::vec3, glm::vec3> LaiEngine::Math::GetTangential(const glm::vec3 & v)
{
	glm::vec3 a = (std::fabs(v.y) > 0.0f || std::fabs(v.z) > 0.0f) ? glm::vec3(1.f, 0.f, 0.f) : glm::vec3(0.f, 1.f, 0.f);
	a = glm::cross(a, v);
	a = glm::normalize(a);
	glm::vec3 b = glm::cross(v, a);
	return std::make_tuple(a, b);
}

glm::vec3 LaiEngine::Math::GetuniformSampleCone(float u1, float u2, const glm::vec3 & axis, float angle)
{
	angle = glm::radians(angle);
	float cosAngle_2 = glm::cos(angle * 0.5f);
	float y = 1.0f - (1.0f - cosAngle_2) * u1;

	float r = glm::sqrt(std::max(0.0f, 1.0f - y * y));
	float phi = Const::TWO_PI * u2;

	float x = r * glm::cos(phi);
	float z = r * glm::sin(phi);

	auto ts = GetTangential(axis);

	return std::get<0>(ts) * x + axis * y + std::get<1>(ts) * z;
}

float LaiEngine::Math::Random()
{
	static std::mt19937 seed;
	std::uniform_real_distribution<float> d(0.0, 1.0);
	return d(seed);
}
