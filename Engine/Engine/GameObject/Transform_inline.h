#pragma once

#include "Transform.h"

#include <glm/gtx/quaternion.hpp>

inline LaiEngine::Transform::Transform()
{

}

inline LaiEngine::Transform::Transform(const glm::vec3 & position, const glm::quat & rotation)
{
	SetPosition(position); 
	SetRotation(rotation);
}

inline void LaiEngine::Transform::SetPosition(const glm::vec3 & position)
{
	mPosition = position;
}

inline const glm::vec3 & LaiEngine::Transform::GetPosition() const
{
	return mPosition;
}

inline void LaiEngine::Transform::SetRotation(const glm::quat & rotation)
{
	mRotation = rotation;
	mOrientationMatrix = glm::toMat3(rotation);
	mInverseOrientationMatrix = glm::toMat3(glm::inverse(rotation));
}

inline const glm::quat & LaiEngine::Transform::GetRotation() const
{
	return mRotation;
}

inline glm::vec3 LaiEngine::Transform::ToLocal(const glm::vec3 & pointInWorld) const
{
	return mInverseOrientationMatrix * (pointInWorld - mPosition);
}

inline glm::vec3 LaiEngine::Transform::ToLocalDirection(const glm::vec3 & dirInWorld) const
{
	return mInverseOrientationMatrix * dirInWorld;
}

inline LaiEngine::Physics::Ray LaiEngine::Transform::ToLocal(const Physics::Ray& rayInWorld) const
{
	return Physics::Ray(ToLocal(rayInWorld.Origin), ToLocalDirection(rayInWorld.Direction));
}

inline glm::vec3 LaiEngine::Transform::ToWorld(const glm::vec3 & pointInLocal) const
{
	return (mOrientationMatrix * pointInLocal) + mPosition;
}

inline glm::vec3 LaiEngine::Transform::ToWorldDirection(const glm::vec3 & dirInLocal) const
{
	return mOrientationMatrix * dirInLocal;
}

inline LaiEngine::Physics::Ray LaiEngine::Transform::ToWorld(const Physics::Ray & rayInLocal) const
{
	return Physics::Ray(ToWorld(rayInLocal.Origin), ToWorldDirection(rayInLocal.Direction));
}


