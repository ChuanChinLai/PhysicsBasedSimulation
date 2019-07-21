#pragma once

#include <Shader/BasicShader.h>

#include <PhysicsAnimation/SimpleMassSpringAnimation.h>
#include <PhysicsAnimation/FountainAnimation.h>

namespace LaiEngine
{
	class ExampleScene : public IGameScene
	{
	public:

		ExampleScene(const SceneManager& sceneManager);
		~ExampleScene();

		void Init()	override;
		void Update(const float dt) override;
		void FixedUpdate(const float dt) override;
		void Release() override;

		void Draw(std::weak_ptr<sf::RenderWindow> window) override;
		void InputProcess(std::weak_ptr<sf::RenderWindow> window, sf::Event& event) override;

	private:

		void BindInstanceBuffer(const std::vector<glm::vec3>& positions);
		GLuint mInstanceBufferId;

		Model mModel;
		BasicShader mShader;
		FirstPersonCamera mCamera;

		FountainAnimation mAnimation;

	};
}