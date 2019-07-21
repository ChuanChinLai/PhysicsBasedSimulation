#pragma once

#include "ICamera.h"

namespace LaiEngine
{
	class FirstPersonCamera : public ICamera
	{
	public:

		FirstPersonCamera(const glm::vec3& pos);

		void Update(const float dt) override;

		void SetSpeed(const float speed);

		void KeyboardInput(std::weak_ptr<sf::RenderWindow> window, sf::Event& event) override;
		void MouseInput(std::weak_ptr<sf::RenderWindow>  window, sf::Event& event) override;

		glm::vec3 velocity;

	private:

		void MakeViewMatrix();
		void MakeProjectionMatrix();

		float mSpeed = 1.0f;
	};
}