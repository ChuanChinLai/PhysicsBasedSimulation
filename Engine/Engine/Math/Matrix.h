#pragma once

#include <glm/mat4x4.hpp>

namespace LaiEngine
{
	class GameObject;
	class ICamera;

	//glm::mat4 MakeModelMatrix(GameObject* object);
	glm::mat4 MakeViewMatrix(const ICamera& camera);
	glm::mat4 MakeProjectionMatrix();
}