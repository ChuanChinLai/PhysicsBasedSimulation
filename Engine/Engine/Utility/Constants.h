#pragma once

#include <glm/vec3.hpp>

#include <cmath>
#include <limits>

namespace LaiEngine
{
	namespace Const
	{
		constexpr size_t ZERO = 0;

		const glm::vec3 GRAVITY = { 0.0f, -9.8f, 0.0f };

		//! Float-type pi.
		constexpr float PI = 3.14159265358979323846264338327950288f;

		//! Float-type 2*pi.
		constexpr float TWO_PI = 2.0f * PI;

		//! Float-type pi/2.
		constexpr float HALF_PI = 1.57079632679489661923132169163975144f;

		//! Max float
		constexpr float FMAX = std::numeric_limits<float>::max();
	}
}