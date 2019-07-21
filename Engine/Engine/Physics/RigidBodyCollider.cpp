#include "RigidBodyCollider.h"

#include <Engine/Geometry/ISurface.h>

LaiEngine::Physics::RigidBodyCollider::RigidBodyCollider(std::shared_ptr<ISurface> surface)
{
	SetSurface(surface);
}

LaiEngine::Physics::RigidBodyCollider::RigidBodyCollider(std::shared_ptr<ISurface> surface, const glm::vec3& linearVel, const glm::vec3& angularVel) : LinearVelocity(linearVel), AngularVelocity(angularVel)
{
	SetSurface(surface);
}

glm::vec3 LaiEngine::Physics::RigidBodyCollider::VelocityAt(const glm::vec3 & point) const
{
	glm::vec3 r = point - GetSurface().mTransform.GetPosition();
	return LinearVelocity + glm::cross(AngularVelocity, r);
}
