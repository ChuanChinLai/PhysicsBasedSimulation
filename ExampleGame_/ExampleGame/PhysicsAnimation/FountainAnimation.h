#pragma once

#include "IPhysicsAnimation.h"

#include <Engine/Engine.h>

namespace LaiEngine
{
	namespace Physics
	{
		class ICollider;
	}

	class PointParticleEmitter;
	class ParticleSystemData;

	class FountainAnimation : public IPhysicsAnimation
	{
	public:

		void Init() override;
		void Release() override;

		void Draw(std::weak_ptr<sf::RenderWindow> window) override;
		void InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event& event) override;

		void SetCollider(std::shared_ptr<Physics::ICollider> collider);

		const std::vector<glm::vec3>& GetPositions();

	private:

		void BeginAdvanceTimeStep(const float dt) override;
		void EndAdvanceTimeStep(const float dt) override;

		void AccumulateForces(const float dt) override;
		void TimeIntegration(const float dt) override;
		void ResolveCollision(const float dt) override;
		void ResolveCollision(std::vector<glm::vec3>& newPositions, std::vector<glm::vec3>& newVelocities);

		std::shared_ptr<PointParticleEmitter> mParticleEmitter;
		std::shared_ptr<ParticleSystemData>   mParticleSystemData;
		std::shared_ptr<Physics::ICollider> mCollider;

		float mRestitutionCoefficient = 0.0f;
		glm::vec3 gravity = { 0.0f, -9.8f, 0.0f };


		std::vector<glm::vec3> mNewPositions;
		std::vector<glm::vec3> mNewVelocities;
	};

}