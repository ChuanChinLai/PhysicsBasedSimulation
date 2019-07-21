#include "IPhysicsAnimation.h"

void LaiEngine::IPhysicsAnimation::Update(const float dt)
{
	BeginAdvanceTimeStep(dt);
	OnBeginAdvanceTimeStep(dt);

	AccumulateForces(dt);
	TimeIntegration(dt);
	ResolveCollision(dt);

	EndAdvanceTimeStep(dt);
	OnEndAdvanceTimeStep(dt);
}