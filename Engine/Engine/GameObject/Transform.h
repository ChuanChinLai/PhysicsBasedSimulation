#pragma once

#include <Engine/Physics/Ray.h>

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace LaiEngine
{
	class Transform
	{
	public:

		inline Transform();
		inline Transform(const glm::vec3& position, const glm::quat& rotation);

		inline void SetPosition(const glm::vec3& position);
		inline const glm::vec3& GetPosition() const;

		inline void SetRotation(const glm::quat& rotation);
		inline const glm::quat& GetRotation() const;

		glm::vec3 ToLocal(const glm::vec3& pointInWorld) const;
		glm::vec3 ToLocalDirection(const glm::vec3& dirInWorld) const;
		Physics::Ray ToLocal(const Physics::Ray& rayInWorld) const;


		glm::vec3 ToWorld(const glm::vec3& pointInLocal) const;
		glm::vec3 ToWorldDirection(const glm::vec3& dirInLocal) const;
		Physics::Ray ToWorld(const Physics::Ray& rayInLocal) const;

	private:

		glm::vec3 mPosition;
		glm::quat mRotation;

		glm::mat3 mOrientationMatrix;
		glm::mat3 mInverseOrientationMatrix; 
	};
}


#include "Transform_inline.h"