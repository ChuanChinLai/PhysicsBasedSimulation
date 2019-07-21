#include "Plane.h"

LaiEngine::Plane::Plane(const Transform & transform, bool isNormalFlipped) : ISurface(transform, isNormalFlipped)
{
}

LaiEngine::Plane::Plane(const glm::vec3 & normal, const glm::vec3 & point, const Transform & transform, bool isNormalFlipped) : ISurface(transform, isNormalFlipped), mNormal(normal), mPoint(point)
{
}

bool LaiEngine::Plane::IsBounded() const
{
	return false;
}

bool LaiEngine::Plane::IsIntersectsLocal(const Physics::Ray & rayLocal) const
{
	return std::fabs(glm::dot(rayLocal.Direction, mNormal)) > 0.f;
}

glm::vec3 LaiEngine::Plane::ClosestPointLocal(const glm::vec3 & otherPointLocal) const
{
	glm::vec3 r = otherPointLocal - mPoint;
	return r - glm::dot(r, mNormal) * mNormal + mPoint;
}

glm::vec3 LaiEngine::Plane::ClosestNormalLocal(const glm::vec3 & otherPointLocal) const
{
	return mNormal;
}

LaiEngine::SurfaceRayIntersection LaiEngine::Plane::ClosestIntersectionLocal(const Physics::Ray & rayLocal) const
{
	SurfaceRayIntersection intersection;

	float dDotN = glm::dot(rayLocal.Direction, mNormal);

	if (std::fabs(dDotN) > 0.f)
	{
		float t = glm::dot(mNormal, mPoint - rayLocal.Origin) / dDotN;

		if (t >= 0.0f)
		{
			intersection.isIntersecting = true;
			intersection.distance = t;
			intersection.point = rayLocal.PointAt(t);
			intersection.normal = mNormal;
		}
	}

	return intersection;
}
