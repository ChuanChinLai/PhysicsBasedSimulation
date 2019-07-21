#pragma once

#include "Ray.h"

inline LaiEngine::Physics::Ray::Ray() : Ray(glm::vec3(), glm::vec3(1.f, 0.f, 0.f))
{
}

inline LaiEngine::Physics::Ray::Ray(const glm::vec3 & newOrigin, const glm::vec3 & newDirection) : Origin(newOrigin), Direction(newDirection)
{
}

inline LaiEngine::Physics::Ray::Ray(const Ray & other) : Origin(other.Origin), Direction(other.Direction)
{
}

inline glm::vec3 LaiEngine::Physics::Ray::PointAt(const float t) const
{
	return Origin + t * Direction;
}
