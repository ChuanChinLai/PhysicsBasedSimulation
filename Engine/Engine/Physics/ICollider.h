#pragma once

#include <glm/vec3.hpp>

#include <memory>

namespace LaiEngine
{
	class ISurface;

	namespace Physics
	{
		class ICollider
		{
		public:

			ICollider() {};

			virtual ~ICollider() {};

			void Update(const float dt);

			void SetSurface(std::shared_ptr<ISurface> surface);
			const ISurface& GetSurface() const;

			void SetFrictionCoeffient(const float coeffient);

			virtual glm::vec3 VelocityAt(const glm::vec3& point) const = 0;
			void ResolveCollision(float radius, float restitutionCoefficient, glm::vec3& newPosition, glm::vec3& newVelocity);

		protected:
			//! Internal query result structure.
			struct ColliderQueryResult final
			{
				glm::vec3 point;
				glm::vec3 normal;
				glm::vec3 velocity;

				float distance;
			};

			//! Outputs closest point's information.
			void GetClosestPoint(std::shared_ptr<ISurface>& surface, const glm::vec3& queryPoint, ColliderQueryResult& result) const;

			bool IsPenetrating(const ColliderQueryResult& colliderPoint, const glm::vec3& position, float radius);

		private:

			float mFrictionCoeffient = 0.0;

			std::shared_ptr<ISurface> mSurface;
		};
	}
}