#include "IParticleEmitter.h"
#include "ParticleSystemData.h"

LaiEngine::IParticleEmitter::IParticleEmitter()
{
}

LaiEngine::IParticleEmitter::~IParticleEmitter()
{
}


std::weak_ptr<LaiEngine::ParticleSystemData> LaiEngine::IParticleEmitter::GetParticleSystem() const
{
	return mParticleSystemData;
}

void LaiEngine::IParticleEmitter::SetParticleSystem(std::weak_ptr<ParticleSystemData> target)
{
	mParticleSystemData = target;
}
