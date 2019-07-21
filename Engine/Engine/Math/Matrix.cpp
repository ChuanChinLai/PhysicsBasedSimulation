#include "Matrix.h"

#include <Engine/Camera/ICamera.h>

#include <glm/gtc/matrix_transform.hpp>

//glm::mat4 LaiEngine::MakeModelMatrix(GameObject* object)
//{
//	glm::mat4 matrix;
//
//	matrix = glm::rotate(matrix, glm::radians(object->rotation.x), { 1, 0, 0 });
//	matrix = glm::rotate(matrix, glm::radians(object->rotation.y), { 0, 1, 0 });
//	matrix = glm::rotate(matrix, glm::radians(object->rotation.z), { 0, 0, 1 });
//
//	matrix = glm::translate(matrix, object->position);
//
//	return matrix;
//}

glm::mat4 LaiEngine::MakeViewMatrix(const ICamera& camera)
{
	glm::mat4 matrix(1.f);

	matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, -camera.position);

	return matrix;
}

glm::mat4 LaiEngine::MakeProjectionMatrix()
{
	constexpr float fov = 90.0f;
	constexpr float aspect = 1.0f;
	constexpr float near = 0.1f;
	constexpr float far = 2000.0f;

	return glm::perspective(glm::radians(fov), aspect, near, far);
}
