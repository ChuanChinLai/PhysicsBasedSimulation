#include "PointParticleEmitter.h"

#include <ParticleSystem/ParticleSystemData.h>

#include <Engine/Math/Math.h>

LaiEngine::PointParticleEmitter::PointParticleEmitter(
	const glm::vec3 & origin, 
	const glm::vec3 & direction, 
	const float speed, 
	const float spreadAngleInDegrees): 
	mOrigin(origin), 
	mDirection(direction), 
	mSpeed(speed), 
	mSpreadAngleInDegrees(spreadAngleInDegrees)
{

}

void LaiEngine::PointParticleEmitter::Update(const float dt)
{
	std::vector<glm::vec3> positions; 
	std::vector<glm::vec3> velocities;

	Emit(positions, velocities, 1);

	if (auto system = mParticleSystemData.lock())
	{
		system->AddParticles(positions, velocities);
	}
}

void LaiEngine::PointParticleEmitter::Emit(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& velocities, size_t numberOfParticles)
{
	for (size_t i = 0; i < numberOfParticles; i++)
	{
		glm::vec3 dir = Math::GetuniformSampleCone(Math::Random(), Math::Random(), mDirection, mSpreadAngleInDegrees);
		positions.push_back(mOrigin); 
		velocities.push_back(mSpeed * dir);
	}
}
