#include "ICollider.h"

#include <Engine/Geometry/ISurface.h>

#include <algorithm>
#include <iostream>

void LaiEngine::Physics::ICollider::Update(const float dt)
{
}

void LaiEngine::Physics::ICollider::SetSurface(std::shared_ptr<ISurface> surface)
{
	mSurface = surface;
}

const LaiEngine::ISurface & LaiEngine::Physics::ICollider::GetSurface() const
{
	return *mSurface;
}

void LaiEngine::Physics::ICollider::SetFrictionCoeffient(const float coeffient)
{
	mFrictionCoeffient = coeffient;
}

void LaiEngine::Physics::ICollider::ResolveCollision(float radius, float restitutionCoefficient, glm::vec3 & newPosition, glm::vec3 & newVelocity)
{
	if (mSurface == nullptr || !mSurface->IsValidGeometry())
	{
		return;
	}

	ColliderQueryResult colliderPoint;

	GetClosestPoint(mSurface, newPosition, colliderPoint);

	if (IsPenetrating(colliderPoint, newPosition, radius))
	{
		glm::vec3 targetNormal = colliderPoint.normal;
		glm::vec3 targetPoint = colliderPoint.point + radius * targetNormal;
		glm::vec3 colliderVelAtTargetPoint = colliderPoint.velocity;


		// Get new candidate relative velocity from the target point.
		glm::vec3 relativeVel = newVelocity - colliderVelAtTargetPoint;
		float normalDotRelativeVel = glm::dot(targetNormal, relativeVel);
		glm::vec3 relativeVelN = normalDotRelativeVel * targetNormal;
		glm::vec3 relativeVelT = relativeVel - relativeVelN;

		if (normalDotRelativeVel < 0.0f)
		{
			glm::vec3 deltaRelativeVelN = (-restitutionCoefficient - 1.0f) * relativeVelN;
			relativeVelN *= -restitutionCoefficient;


			// http://graphics.stanford.edu/papers/cloth-sig02/cloth.pdf
			if (relativeVelT.length() > 0.0f) 
			{
				float frictionScale = std::max(1.0f - mFrictionCoeffient * deltaRelativeVelN.length() / relativeVelT.length(), 0.0f);
				relativeVelT *= frictionScale;
			}

			newVelocity = relativeVelN + relativeVelT + colliderVelAtTargetPoint;
		}

		newPosition = targetPoint;
	}
}

void LaiEngine::Physics::ICollider::GetClosestPoint(std::shared_ptr<ISurface>& surface, const glm::vec3 & queryPoint, ColliderQueryResult& result) const
{
	result.distance = surface->ClosestDistance(queryPoint);
	result.point = surface->ClosestPoint(queryPoint);
	result.normal = surface->ClosestNormal(queryPoint);
	result.velocity = VelocityAt(queryPoint);
}

bool LaiEngine::Physics::ICollider::IsPenetrating(const ColliderQueryResult & colliderPoint, const glm::vec3 & position, float radius)
{
	return mSurface->IsInside(position) || colliderPoint.distance < radius;
}
