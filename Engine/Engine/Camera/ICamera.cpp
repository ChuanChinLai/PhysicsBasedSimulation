#include "ICamera.h"

#include <memory>

const glm::mat4& LaiEngine::ICamera::GetViewMatrix() const noexcept
{
	return mViewMatrix;
}

const glm::mat4& LaiEngine::ICamera::GetProjectedMatrix() const noexcept
{
	return mProjectedMatrix;
}

const glm::mat4& LaiEngine::ICamera::GetProjectedViewMatrix() const noexcept
{
	return mProjectedViewMatrix;
}

void LaiEngine::ICamera::InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event & event)
{
	KeyboardInput(window, event);
	MouseInput(window, event);
}