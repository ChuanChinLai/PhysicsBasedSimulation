#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>

#include <vector>

namespace LaiEngine
{
	struct sVertex
	{
		glm::vec3 Position;
		glm::vec3 Color;
	};

	class Mesh
	{
	public:

		virtual ~Mesh() {};

		std::vector<sVertex> vertices;
		std::vector<GLuint>  indices;
	};


	class Cube : public Mesh
	{
	public:
		Cube(); 
	};
}
