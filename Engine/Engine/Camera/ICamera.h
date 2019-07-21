#pragma once

#include <Engine/Utility/NonCopyable.h>
#include <Engine/Utility/NonMovable.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
	class Event;
}

namespace LaiEngine
{
	class ICamera : public NonMovable, public NonCopyable
	{
	public:

		virtual ~ICamera() {};
	
		virtual void Update(const float dt) = 0;

		const glm::mat4& GetViewMatrix() const noexcept;
		const glm::mat4& GetProjectedMatrix() const noexcept;
		const glm::mat4& GetProjectedViewMatrix() const noexcept;

		glm::vec3 position;
		glm::vec3 rotation;

		void InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event& event);

	protected:

		virtual void KeyboardInput(std::weak_ptr<sf::RenderWindow>  window, sf::Event& event) = 0;
		virtual void MouseInput(std::weak_ptr<sf::RenderWindow>  window, sf::Event& event) = 0;

		glm::mat4 mProjectedMatrix;
		glm::mat4 mViewMatrix;
		glm::mat4 mProjectedViewMatrix;
	};
}