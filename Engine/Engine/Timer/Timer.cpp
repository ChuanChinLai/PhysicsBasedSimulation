#include "Timer.h"

void LaiEngine::Timer::Update()
{
	mdt = mClock.restart().asSeconds();

	mSimulationTime += mdt;
	mTimeElapsed += mdt;
}

const float & LaiEngine::Timer::GetdT() const
{
	return mdt;
}

const float & LaiEngine::Timer::GetSimulationTime() const
{
	return mSimulationTime;
}

void LaiEngine::Timer::ResetSimulationTime()
{
	mSimulationTime = 0.0f;
}

const float & LaiEngine::Timer::GetTimeElapsed() const
{
	return mTimeElapsed;
}

void LaiEngine::Timer::ResetTimeElapsed()
{
	mTimeElapsed = 0.0f;
}