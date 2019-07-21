#pragma once

#include "IParticleEmitter.h"

#include <glm/vec3.hpp>

#include <vector>

namespace LaiEngine
{
	class PointParticleEmitter : public IParticleEmitter
	{
	public:

		PointParticleEmitter(const glm::vec3& origin, const glm::vec3& direction, const float speed, const float spreadAngleInDegrees);

		void Update(const float dt) override;

	private:

		void Emit(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& velocities, size_t numberOfParticles);

		glm::vec3 mOrigin;
		glm::vec3 mDirection;

		float mSpeed;
		float mSpreadAngleInDegrees;
	};
}