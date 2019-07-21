#pragma once

#include <Engine/Utility/NonCopyable.h>
#include <Engine/Utility/NonMovable.h>

#include <memory>

namespace LaiEngine
{
	class ParticleSystemData;

	class IParticleEmitter : public NonMovable, public NonCopyable
	{
	public:
		IParticleEmitter();
		virtual ~IParticleEmitter();
		
		virtual void Update(const float dt) = 0;

		std::weak_ptr<ParticleSystemData> GetParticleSystem() const;
		void SetParticleSystem(std::weak_ptr<ParticleSystemData> target);

	protected:

		std::weak_ptr<ParticleSystemData> mParticleSystemData;
	};
}