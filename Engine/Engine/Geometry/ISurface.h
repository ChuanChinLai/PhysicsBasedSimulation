#pragma once

#include <Engine/GameObject/Transform.h>
#include <Engine/Utility/Constants.h>
#include <Engine/Physics/Ray.h>

namespace LaiEngine
{
	struct SurfaceRayIntersection
	{
		glm::vec3 point;
		glm::vec3 normal;
		float distance = Const::FMAX;
		bool  isIntersecting = false;
	};

	class ISurface
	{
	public:

		ISurface(const Transform& transform = Transform(), bool isNormalFlipped = false);
		ISurface(const ISurface& other);

		virtual ~ISurface() {};


		bool IsInside(const glm::vec3& otherPoint) const;
		bool IsIntersects(const Physics::Ray& ray) const;


		float ClosestDistance(const glm::vec3& otherPoint) const;
		glm::vec3 ClosestPoint(const glm::vec3& otherPoint) const;
		glm::vec3 ClosestNormal(const glm::vec3& otherPoint) const;
		SurfaceRayIntersection ClosestIntersection(const Physics::Ray& ray) const;


		virtual bool IsBounded() const;
		virtual bool IsValidGeometry() const;


		Transform mTransform;
		bool mIsNormalFlipped = false;

	protected:

		virtual bool IsInsideLocal(const glm::vec3& otherPointLocal) const;
		virtual bool IsIntersectsLocal(const Physics::Ray& rayLocal) const;


		virtual float ClosestDistanceLocal(const glm::vec3& otherPointLocal) const;
		virtual glm::vec3 ClosestPointLocal(const glm::vec3& otherPointLocal) const = 0;
		virtual glm::vec3 ClosestNormalLocal(const glm::vec3& otherPointLocal) const = 0;
		virtual SurfaceRayIntersection ClosestIntersectionLocal(const Physics::Ray& rayLocal) const = 0;

	};

}