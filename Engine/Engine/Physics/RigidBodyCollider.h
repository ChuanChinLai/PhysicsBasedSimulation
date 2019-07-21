#pragma once

#include "ICollider.h"

namespace LaiEngine
{
	class ISurface;

	namespace Physics
	{
		class RigidBodyCollider : public ICollider
		{
		public:
			explicit RigidBodyCollider(std::shared_ptr<ISurface> surface);
			RigidBodyCollider(std::shared_ptr<ISurface> surface, const glm::vec3& linearVel, const glm::vec3& angularVel);

			glm::vec3 VelocityAt(const glm::vec3& point) const override;

			glm::vec3 LinearVelocity;
			glm::vec3 AngularVelocity;
		};
	}
}