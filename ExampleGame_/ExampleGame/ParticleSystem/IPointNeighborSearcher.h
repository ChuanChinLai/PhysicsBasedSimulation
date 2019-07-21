#pragma once

#include <Engine/Engine.h>

namespace LaiEngine
{
	class IPointNeighborSearcher : public NonMovable, public NonCopyable
	{
	public:

		typedef std::function<void(size_t, const glm::vec3&)> ForEachNearbyPointFunc;


		IPointNeighborSearcher() {};
		virtual ~IPointNeighborSearcher() {};

	
		virtual void Build(const std::vector<glm::vec3>& points) = 0;

		virtual void ForEachNearbyPoint(const glm::vec3& origin, float radius, const ForEachNearbyPointFunc& callback) const = 0;
	};
}