#include "ExampleScene.h"

#include <Engine/Engine.h>

#include <iostream>

LaiEngine::ExampleScene::ExampleScene(const SceneManager & sceneManager) : IGameScene(sceneManager), mCamera(glm::vec3(0, 5, 10))
{

}

LaiEngine::ExampleScene::~ExampleScene()
{

}

void LaiEngine::ExampleScene::Init()
{
	mAnimation.Init();
	mCamera.SetSpeed(1.0f);

	glGenBuffers(1, &mInstanceBufferId);

	Mesh mesh = Cube();

	mModel.Init(mesh);
}

void LaiEngine::ExampleScene::Update(const float dt)
{
	mCamera.Update(dt);
}

void LaiEngine::ExampleScene::FixedUpdate(const float dt)
{
	mAnimation.Update(dt);
}

void LaiEngine::ExampleScene::Release()
{

}

void LaiEngine::ExampleScene::Draw(std::weak_ptr<sf::RenderWindow> window)
{
	mShader.UseProgram();
	mShader.SetViewMat(mCamera.GetViewMatrix());
	mShader.SetProjectedMat(mCamera.GetProjectedMatrix());

	mModel.BindVAO();

	const std::vector<glm::vec3>& positions = mAnimation.GetPositions();

	BindInstanceBuffer(positions);

	const GLsizei numElements = static_cast<GLsizei>(mModel.GetIndexCount());
	const GLsizei numInstances = static_cast<GLsizei>(positions.size());

	glDrawElementsInstanced(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, nullptr, numInstances);
	glBindVertexArray(0);
}

void LaiEngine::ExampleScene::InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event & event)
{
	mCamera.InputProcess(window, event);
}

void LaiEngine::ExampleScene::BindInstanceBuffer(const std::vector<glm::vec3>& positions)
{
	const auto size = positions.size();

	if (size == 0) return;

	glBindBuffer(GL_ARRAY_BUFFER, mInstanceBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * size, positions.data(), GL_STATIC_DRAW);

	constexpr GLuint vertexElementLocation = 2;
	constexpr GLint elementCount = 3;
	constexpr GLboolean notNormalized = GL_FALSE;
	constexpr auto stride = static_cast<GLsizei>(3 * sizeof(float));
	GLvoid* offset = reinterpret_cast<GLvoid*>(0);

	glVertexAttribPointer(vertexElementLocation, elementCount, GL_FLOAT, notNormalized, stride, offset);
	glVertexAttribDivisor(vertexElementLocation, 1); // tell OpenGL this is an instanced vertex attribute.

	const auto errorCode = glGetError();
	if (errorCode == GL_NO_ERROR)
	{
		glEnableVertexAttribArray(vertexElementLocation);
		const GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::string message = "OpenGL failed to enable the offset vertex attribute at location: " + vertexElementLocation;
			throw std::runtime_error(message.c_str());
		}
	}
	else
	{
		throw std::runtime_error("OpenGL failed to set the offset vertex attribute at location: " + vertexElementLocation);
	}


	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
