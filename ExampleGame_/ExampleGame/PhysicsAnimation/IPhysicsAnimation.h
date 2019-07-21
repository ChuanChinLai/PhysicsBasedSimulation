#pragma once

#include <Engine/Engine.h>

#include <memory>

namespace sf
{
	class RenderWindow;
	class Event;
}

namespace LaiEngine
{
	class IPhysicsAnimation : public NonMovable, public NonCopyable
	{
	public:

		void Update(const float dt);

	protected:

		IPhysicsAnimation() = default;
		virtual ~IPhysicsAnimation() {};

		virtual void Init()	= 0;
		virtual void Release() = 0;

		virtual void Draw(std::weak_ptr<sf::RenderWindow> window) {};
		virtual void InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event& event) {};


		virtual void BeginAdvanceTimeStep(const float dt) {};
		virtual void OnBeginAdvanceTimeStep(const float dt) {};

		virtual void EndAdvanceTimeStep(const float dt) {};
		virtual void OnEndAdvanceTimeStep(const float dt) {};


		virtual void AccumulateForces(const float dt) = 0;
		virtual void TimeIntegration(const float dt)  = 0;
		virtual void ResolveCollision(const float dt) = 0;
	};
}