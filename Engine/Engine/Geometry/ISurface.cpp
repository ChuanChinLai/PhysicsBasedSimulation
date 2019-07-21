#include "ISurface.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

LaiEngine::ISurface::ISurface(const Transform & transform, bool isNormalFlipped) : mTransform(transform), mIsNormalFlipped(isNormalFlipped)
{
}

LaiEngine::ISurface::ISurface(const ISurface & other) : mTransform(other.mTransform), mIsNormalFlipped(other.mIsNormalFlipped)
{

}

bool LaiEngine::ISurface::IsInside(const glm::vec3 & otherPoint) const
{
	return mIsNormalFlipped == !IsInsideLocal(mTransform.ToLocal(otherPoint));
}

bool LaiEngine::ISurface::IsIntersects(const Physics::Ray & ray) const
{
	return IsIntersectsLocal(mTransform.ToLocal(ray));
}

float LaiEngine::ISurface::ClosestDistance(const glm::vec3 & otherPoint) const
{
	return ClosestDistanceLocal(mTransform.ToLocal(otherPoint));
}

glm::vec3 LaiEngine::ISurface::ClosestPoint(const glm::vec3 & otherPoint) const
{
	return mTransform.ToWorld(ClosestPointLocal(mTransform.ToLocal(otherPoint)));
}

glm::vec3 LaiEngine::ISurface::ClosestNormal(const glm::vec3 & otherPoint) const
{
	auto result = mTransform.ToWorldDirection(ClosestNormalLocal(mTransform.ToLocal(otherPoint)));
	result *= (mIsNormalFlipped) ? -1.0f : 1.0f;
	return result;
}

LaiEngine::SurfaceRayIntersection LaiEngine::ISurface::ClosestIntersection(const Physics::Ray & ray) const
{
	auto result = ClosestIntersectionLocal(mTransform.ToLocal(ray));
	result.point = mTransform.ToWorld(result.point);
	result.normal = mTransform.ToWorldDirection(result.normal);
	result.normal *= (mIsNormalFlipped) ? -1.0 : 1.0;
	return result;
}

bool LaiEngine::ISurface::IsBounded() const
{
	return true;
}

bool LaiEngine::ISurface::IsValidGeometry() const
{
	return true;
}

bool LaiEngine::ISurface::IsInsideLocal(const glm::vec3 & otherPointLocal) const
{
	glm::vec3 cpLocal = ClosestPointLocal(otherPointLocal);
	glm::vec3 normalLocal = ClosestNormalLocal(otherPointLocal);

	return glm::dot(otherPointLocal - cpLocal, normalLocal) < 0.0f;
}

bool LaiEngine::ISurface::IsIntersectsLocal(const Physics::Ray & rayLocal) const
{
	auto result = ClosestIntersectionLocal(rayLocal);
	return result.isIntersecting;
}


float LaiEngine::ISurface::ClosestDistanceLocal(const glm::vec3 & otherPointLocal) const
{
	return glm::distance(otherPointLocal, ClosestPointLocal(otherPointLocal));
}