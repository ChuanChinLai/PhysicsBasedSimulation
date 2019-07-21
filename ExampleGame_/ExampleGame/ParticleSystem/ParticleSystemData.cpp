#include "ParticleSystemData.h"

#include <cassert>

LaiEngine::ParticleSystemData::ParticleSystemData() : ParticleSystemData(0)
{

}

LaiEngine::ParticleSystemData::ParticleSystemData(size_t numberOfParticles)
{
	mPositionIdx = AddAttribute();
	mVelocityIdx = AddAttribute();
	mForceIdx    = AddAttribute();

	Resize(numberOfParticles);
}

LaiEngine::ParticleSystemData::~ParticleSystemData()
{
}

void LaiEngine::ParticleSystemData::Resize(const size_t newsize)
{
	mNumOfParticles = newsize;

	for (auto& attr : mDataList)
	{
		attr.resize(newsize, glm::vec3());
	}
}

void LaiEngine::ParticleSystemData::AddParticle(const glm::vec3 & position, const glm::vec3 & velocity, const glm::vec3 & force)
{
	std::vector<glm::vec3> positions  = { position };
	std::vector<glm::vec3> velocities = { velocity };
	std::vector<glm::vec3> forces     = { force    };

	AddParticles(positions, velocities, forces);
}

void LaiEngine::ParticleSystemData::AddParticles(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& velocities, const std::vector<glm::vec3>& forces)
{
	const size_t n = positions.size();

	if (n == 0) return;

	size_t oldNumberOfParticles = mNumOfParticles;
	size_t newNumberOfParticles = oldNumberOfParticles + n;

	Resize(newNumberOfParticles);

	auto& pos = Positions();
	auto& vel = Velocities();
	auto& frc = Forces();


	Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i) 
	{
		pos[i + oldNumberOfParticles] = positions[i];
	});

	if (velocities.size() > 0)
	{
		Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i)
		{
			vel[i + oldNumberOfParticles] = velocities[i];
		});
	}

	if (forces.size() > 0)
	{
		Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i)
		{
			frc[i + oldNumberOfParticles] = forces[i];
		});
	}
}

float LaiEngine::ParticleSystemData::Mass() const
{
	return mMass;
}

void LaiEngine::ParticleSystemData::SetMass(const float mass)
{
	mMass = mass;
}

float LaiEngine::ParticleSystemData::ParticleRadius() const
{
	return mParticleRadius;
}

void LaiEngine::ParticleSystemData::SetParticleRadius(const float radius)
{
	mParticleRadius = radius;
}

size_t LaiEngine::ParticleSystemData::NumberOfParticles() const
{
	return mNumOfParticles;
}

std::vector<glm::vec3> & LaiEngine::ParticleSystemData::Positions()
{
	return mDataList[mPositionIdx];
}

const std::vector<glm::vec3> & LaiEngine::ParticleSystemData::Positions() const
{
	return mDataList[mPositionIdx];
}

std::vector<glm::vec3> & LaiEngine::ParticleSystemData::Velocities()
{
	return mDataList[mVelocityIdx];
}

const std::vector<glm::vec3> & LaiEngine::ParticleSystemData::Velocities() const
{
	return mDataList[mVelocityIdx];
}

std::vector<glm::vec3> & LaiEngine::ParticleSystemData::Forces()
{
	return mDataList[mForceIdx];
}

const std::vector<glm::vec3> & LaiEngine::ParticleSystemData::Forces() const
{
	return mDataList[mForceIdx];
}

size_t LaiEngine::ParticleSystemData::AddAttribute(const std::vector<glm::vec3>& val)
{
	size_t attrIdx = mDataList.size();
	mDataList.emplace_back(val);
	return attrIdx;
}
