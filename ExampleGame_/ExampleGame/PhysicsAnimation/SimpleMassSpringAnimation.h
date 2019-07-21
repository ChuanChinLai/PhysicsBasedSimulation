#pragma once

#include "IPhysicsAnimation.h"

#include <ExampleGame/ParticleSystem/ParticleSystemData.h>

#include <vector>

namespace LaiEngine
{
	class SimpleMassSpringAnimation : public IPhysicsAnimation
	{
	public:

		struct Edge
		{
			size_t first; 
			size_t second;
		};

		struct Constraint
		{
			int pointIndex;
			glm::vec3 fixedPosition;
			glm::vec3 fixedVelocity;
		};

		SimpleMassSpringAnimation(size_t numberOfPoints = 10);

		void Init() override;
		void Release() override;

		void Draw(std::weak_ptr<sf::RenderWindow> window) override;
		void InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event& event) override;

		const std::vector<glm::vec3>& GetPositions();

	private:

		void BeginAdvanceTimeStep(const float dt) override;
		void EndAdvanceTimeStep(const float dt) override;

		void AccumulateForces(const float dt) override;
		void TimeIntegration(const float dt) override;
		void ResolveCollision(const float dt) override;


		ParticleSystemData mParticleSystemData;

		std::vector<Edge> mEdges;

		std::vector<Constraint> mConstraints;


		glm::vec3 gravity = { 0.0f, -9.8f, 0.0f };
		float mMass = 1.0f;
	};
}