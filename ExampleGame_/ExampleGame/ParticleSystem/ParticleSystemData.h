#pragma once

#include <Engine/Engine.h>

namespace LaiEngine
{
	class ParticleSystemData : public NonMovable, public NonCopyable
	{
	public:

		ParticleSystemData();
		ParticleSystemData(size_t numberOfParticles);

		virtual ~ParticleSystemData();

		void Resize(const size_t newsize);

		void AddParticle(const glm::vec3& position, const glm::vec3& velocity = glm::vec3(), const glm::vec3& force = glm::vec3());

		void AddParticles(
			const std::vector<glm::vec3>& positions, 
			const std::vector<glm::vec3>& velocities = std::vector<glm::vec3>(),
			const std::vector<glm::vec3>& forces = std::vector<glm::vec3>());


		float Mass() const;
		virtual void SetMass(const float mass);

		float ParticleRadius() const;
		virtual void SetParticleRadius(const float radius);


		size_t NumberOfParticles() const;

		std::vector<glm::vec3>& Positions();
		const std::vector<glm::vec3>& Positions() const;

		std::vector<glm::vec3>& Velocities();
		const std::vector<glm::vec3>& Velocities() const;

		std::vector<glm::vec3>& Forces();
		const std::vector<glm::vec3>& Forces() const;


	protected:

		size_t AddAttribute(const std::vector<glm::vec3>& val = std::vector<glm::vec3>());

	private:

		float mMass = 1.0f;
		float mParticleRadius = 1e-3f;

		size_t mNumOfParticles = 0;
		size_t mPositionIdx;
		size_t mVelocityIdx;
		size_t mForceIdx;

		std::vector<std::vector<glm::vec3>> mDataList;
	};
}

