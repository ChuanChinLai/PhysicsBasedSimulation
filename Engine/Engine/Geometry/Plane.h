#pragma once

#include "ISurface.h"

namespace LaiEngine
{
	class Plane final : public ISurface
	{
	public:

		//! Constructs a plane that crosses (0, 0, 0) with surface normal (0, 1, 0).
		Plane(const Transform& transform = Transform(), bool isNormalFlipped = false);

		//! Constructs a plane that cross \p point with surface normal \p normal.
		Plane(const glm::vec3& normal, const glm::vec3& point, const Transform& transform = Transform(), bool isNormalFlipped = false);

		bool IsBounded() const override ;

		glm::vec3 mPoint;
		glm::vec3 mNormal = glm::vec3(0.f, 1.f, 0.f);

	private:

		bool IsIntersectsLocal(const Physics::Ray& rayLocal) const override;

		glm::vec3 ClosestPointLocal(const glm::vec3& otherPointLocal) const override;
		glm::vec3 ClosestNormalLocal(const glm::vec3& otherPointLocal) const override;
		SurfaceRayIntersection ClosestIntersectionLocal(const Physics::Ray& rayLocal) const override;
	};

}