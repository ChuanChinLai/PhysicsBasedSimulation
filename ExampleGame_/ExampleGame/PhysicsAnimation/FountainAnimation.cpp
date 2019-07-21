#include "FountainAnimation.h"

#include <ExampleGame/ParticleSystem/PointParticleEmitter.h>
#include <ExampleGame/ParticleSystem/ParticleSystemData.h>

void LaiEngine::FountainAnimation::Init()
{
	glm::vec3 origin = { 0.f, 0.f, 0.f };
	glm::vec3 dir = { 0.f, 1.f, 0.f };

	mParticleSystemData = std::make_shared<ParticleSystemData>();
	mParticleEmitter = std::make_shared<PointParticleEmitter>(origin, dir, 20.0f, 60.0f);
	mParticleEmitter->SetParticleSystem(mParticleSystemData);


	std::shared_ptr<Plane> plane = std::make_shared<Plane>(glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, -5.f, 0.f));
	mCollider = std::make_shared<Physics::RigidBodyCollider>(plane);
}

void LaiEngine::FountainAnimation::Release()
{
}

void LaiEngine::FountainAnimation::Draw(std::weak_ptr<sf::RenderWindow> window)
{
}

void LaiEngine::FountainAnimation::InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event & event)
{
}

void LaiEngine::FountainAnimation::SetCollider(std::shared_ptr<Physics::ICollider> collider)
{
	mCollider = collider;
}

const std::vector<glm::vec3>& LaiEngine::FountainAnimation::GetPositions()
{
	return mParticleSystemData->Positions();
}

void LaiEngine::FountainAnimation::BeginAdvanceTimeStep(const float dt)
{
	mParticleEmitter->Update(dt);

	size_t n = mParticleSystemData->NumberOfParticles();
	mNewPositions.resize(n);
	mNewVelocities.resize(n);
}

void LaiEngine::FountainAnimation::EndAdvanceTimeStep(const float dt)
{
	size_t n = mParticleSystemData->NumberOfParticles();

	auto& positions = mParticleSystemData->Positions();
	auto& velocities = mParticleSystemData->Velocities();

	Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i)
	{
		positions[i] = mNewPositions[i];
		velocities[i] = mNewVelocities[i];
	});
}

void LaiEngine::FountainAnimation::AccumulateForces(const float dt)
{
	constexpr float dragCoefficient = 0.1f;

	size_t n = mParticleSystemData->NumberOfParticles();

	auto& positions = mParticleSystemData->Positions();
	auto& velocities = mParticleSystemData->Velocities();
	auto& forces = mParticleSystemData->Forces();
	auto mass = mParticleSystemData->Mass();

	Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i) 
	{
		glm::vec3 gForce = mass * gravity;
		gForce += dragCoefficient * velocities[i];
		forces[i] = gForce;
	});
}

void LaiEngine::FountainAnimation::TimeIntegration(const float dt)
{
	size_t n = mParticleSystemData->NumberOfParticles();
	auto mass = mParticleSystemData->Mass();

	auto& positions = mParticleSystemData->Positions();
	auto& velocities = mParticleSystemData->Velocities();
	auto& forces = mParticleSystemData->Forces();


	Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i) 
	{
		glm::vec3 acc = forces[i] / mass;

		glm::vec3& newVel = mNewVelocities[i];
		newVel = velocities[i] + acc * dt;


		glm::vec3& newPos = mNewPositions[i];
		newPos = positions[i] + newVel * dt;
	});
}

void LaiEngine::FountainAnimation::ResolveCollision(const float dt)
{
	ResolveCollision(mNewPositions, mNewVelocities);
}

void LaiEngine::FountainAnimation::ResolveCollision(std::vector<glm::vec3>& newPositions, std::vector<glm::vec3>& newVelocities)
{
	if (mCollider == nullptr)
		return;

	size_t n = mParticleSystemData->NumberOfParticles();
	const float radius = mParticleSystemData->ParticleRadius();

	Concurrency::ParallelFor(Const::ZERO, n, [&](size_t i)
	{
		mCollider->ResolveCollision(radius, mRestitutionCoefficient, newPositions[i], newVelocities[i]);
	});
}
