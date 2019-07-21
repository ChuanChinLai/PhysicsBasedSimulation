#include "SimpleMassSpringAnimation.h"

#include <Engine/Engine.h>

#include <iostream>

LaiEngine::SimpleMassSpringAnimation::SimpleMassSpringAnimation(size_t numberOfPoints)
{
	mParticleSystemData.Resize(numberOfPoints);

	size_t numberOfEdges = numberOfPoints - 1;
	mEdges.resize(numberOfEdges);

	auto& positions = mParticleSystemData.Positions();

	for (int i = 0; i < numberOfPoints; i++)
	{
		positions[i].x = static_cast<float>(-i);
	}

	for (size_t i = 0; i < numberOfEdges; i++)
	{
		mEdges[i] = Edge{ i, i + 1 };
	}


	//add constraints
	{
		Constraint constraint;
		constraint.pointIndex = 0;
		constraint.fixedPosition = glm::vec3(0.f, 0.f, 0.f);
		constraint.fixedVelocity = glm::vec3(0.f, 0.f, 0.f);

		mConstraints.push_back(constraint);
	}
}

void LaiEngine::SimpleMassSpringAnimation::Init()
{

}

void LaiEngine::SimpleMassSpringAnimation::Release()
{

}

void LaiEngine::SimpleMassSpringAnimation::Draw(std::weak_ptr<sf::RenderWindow> window)
{

}

void LaiEngine::SimpleMassSpringAnimation::InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event & event)
{

}

const std::vector<glm::vec3>& LaiEngine::SimpleMassSpringAnimation::GetPositions()
{
	return mParticleSystemData.Positions();
}

void LaiEngine::SimpleMassSpringAnimation::BeginAdvanceTimeStep(const float dt)
{
}

void LaiEngine::SimpleMassSpringAnimation::EndAdvanceTimeStep(const float dt)
{
}

void LaiEngine::SimpleMassSpringAnimation::AccumulateForces(const float dt)
{
	constexpr float dragCoefficient = 0.1f;

	constexpr float restLength = 1.0f;
	constexpr float dampingCoefficient = 1.0f;
	constexpr float springConst = 500.0f;


	size_t n = mParticleSystemData.NumberOfParticles();

	auto& positions = mParticleSystemData.Positions();
	auto& velocities = mParticleSystemData.Velocities();
	auto& forces = mParticleSystemData.Forces();


	Concurrency::ParallelFor(Const::ZERO, n, [&] (size_t i) {
		glm::vec3 gForce = mMass * gravity;
		gForce += dragCoefficient * velocities[i];
		forces[i] = gForce;
	});


	size_t numberOfEdges = n - 1;

	for (size_t i = 0; i < numberOfEdges; i++)
	{
		size_t index0 = mEdges[i].first;
		size_t index1 = mEdges[i].second;

		glm::vec3 pos0 = positions[index0];
		glm::vec3 pos1 = positions[index1];

		glm::vec3 r = pos0 - pos1;

		float distance = glm::length(r);

		if (distance > 0.0f)
		{
			glm::vec3 force = -springConst * (distance - restLength) * glm::normalize(r);

			forces[index0] += force;
			forces[index1] -= force;
		}

		{
			glm::vec3 vec0 = velocities[index0];
			glm::vec3 vec1 = velocities[index1];

			glm::vec3 damping = -dampingCoefficient * (vec0 - vec1);
			forces[index0] += damping;
			forces[index1] -= damping;
		}
	}
}

void LaiEngine::SimpleMassSpringAnimation::TimeIntegration(const float dt)
{
	size_t n = mParticleSystemData.NumberOfParticles();

	auto& positions = mParticleSystemData.Positions();
	auto& velocities = mParticleSystemData.Velocities();
	auto& forces = mParticleSystemData.Forces();

	Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i) {
		glm::vec3 acc = forces[i] / mMass;
		glm::vec3 vec = velocities[i] + acc * dt;
		glm::vec3 pos = positions[i] + vec * dt;

		velocities[i] = vec;
		positions[i] = pos;
	});
}

void LaiEngine::SimpleMassSpringAnimation::ResolveCollision(const float dt)
{
	auto& positions = mParticleSystemData.Positions();
	auto& velocities = mParticleSystemData.Velocities();


	for (int i = 0; i < mConstraints.size(); i++)
	{
		int index = mConstraints[i].pointIndex;

		positions[index] = mConstraints[i].fixedPosition;
		velocities[index] = mConstraints[i].fixedVelocity;
	}
}