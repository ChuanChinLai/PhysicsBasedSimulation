#include "FirstPersonCamera.h"

#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

LaiEngine::FirstPersonCamera::FirstPersonCamera(const glm::vec3 & pos)
{
	position = pos;
}

void LaiEngine::FirstPersonCamera::Update(const float dt)
{
	position += velocity * dt;
	velocity *= 0.95f;

	MakeViewMatrix();
	MakeProjectionMatrix();
}

void LaiEngine::FirstPersonCamera::SetSpeed(const float speed)
{
	mSpeed = speed;
}

void LaiEngine::FirstPersonCamera::KeyboardInput(std::weak_ptr<sf::RenderWindow>  window, sf::Event & event)
{
	glm::vec3 dv;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dv.x = glm::cos(glm::radians(rotation.y + 90.0f)) * mSpeed;
		dv.z = glm::sin(glm::radians(rotation.y + 90.0f)) * mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dv.x = -glm::cos(glm::radians(rotation.y + 90.0f)) * mSpeed;
		dv.z = -glm::sin(glm::radians(rotation.y + 90.0f)) * mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dv.x = glm::cos(glm::radians(rotation.y)) * mSpeed;
		dv.z = glm::sin(glm::radians(rotation.y)) * mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dv.x = -glm::cos(glm::radians(rotation.y)) * mSpeed;
		dv.z = -glm::sin(glm::radians(rotation.y)) * mSpeed;
	}

	velocity += dv;
}

void LaiEngine::FirstPersonCamera::MouseInput(std::weak_ptr<sf::RenderWindow> window, sf::Event & event)
{
	if (window.expired())
		return;

	const sf::RenderWindow& win = *window.lock();

	static auto const BOUND = 80;
	static auto lastMousePosition = sf::Mouse::getPosition(win);
	auto change = sf::Mouse::getPosition() - lastMousePosition;

	rotation.y += static_cast<float>(change.x * 0.05f);
	rotation.x += static_cast<float>(change.y * 0.05f);

	if (rotation.x > BOUND) rotation.x = BOUND;
	else if (rotation.x < -BOUND) rotation.x = -BOUND;

	if (rotation.y > 360.0f) rotation.y = 0.0f;
	else if (rotation.y < 0.0f)    rotation.y = 360.0f;

	auto cx = static_cast<int>(win.getSize().x * 0.5f);
	auto cy = static_cast<int>(win.getSize().y * 0.5f);

	sf::Mouse::setPosition({ cx, cy }, win);

	lastMousePosition = sf::Mouse::getPosition();
}

void LaiEngine::FirstPersonCamera::MakeViewMatrix()
{
	glm::mat4 matrix(1.f);

	matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, -position);

	mViewMatrix = matrix;
}

void LaiEngine::FirstPersonCamera::MakeProjectionMatrix()
{
	constexpr float fov = 90.0f;
	constexpr float aspect = 1.0f;
	constexpr float near = 0.1f;
	constexpr float far = 2000.0f;

	mProjectedMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}
