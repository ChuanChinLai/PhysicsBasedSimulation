#pragma once

#include <Engine/Utility/NonCopyable.h>
#include <Engine/Utility/NonMovable.h>

#include <SFML/Graphics.hpp>

namespace LaiEngine
{
	class Timer : public NonMovable, public NonCopyable
	{
	public:
		
		void Update();

		const float& GetdT() const;

		const float& GetSimulationTime() const;
		void ResetSimulationTime();

		const float& GetTimeElapsed() const;
		void ResetTimeElapsed();

	private:

		sf::Clock mClock;

		float mdt = 0.0f;
		float mSimulationTime = 0.0f;
		float mTimeElapsed = 0.0f;
	};
}