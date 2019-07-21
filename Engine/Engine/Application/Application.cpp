#include "Application.h"

#include <Engine/Scene/SceneManager.h>

#include <SFML/Graphics.hpp>
#include <glad/glad.h>
#include <iostream>

LaiEngine::Engine::Engine(const std::string& title) : mRenderWindow(std::make_shared<sf::RenderWindow>()), mSceneManager(std::make_shared<SceneManager>(*this))
{
	try
	{
		if (!InitGL(title))
		{
			throw std::runtime_error("Failed to initialize OpenGL");
		}
	}
	catch (std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
	}
}

LaiEngine::Engine::~Engine()
{

}

void LaiEngine::Engine::GameLoop()
{

	mIsGameRunning = mRenderWindow->isOpen();

	while (mIsGameRunning)
	{
		mFrameCount++;

		if (mTimer.GetTimeElapsed() >= 1.0f)
		{
			std::cout << "FPS: " << mFrameCount << std::endl;
			mTimer.ResetTimeElapsed();
			mFrameCount = 0;
		}

		mSceneManager->Update(mTimer.GetdT());

		if (mTimer.GetSimulationTime() >= mFixedUpdateTime)
		{
			mTimer.ResetSimulationTime();
			mSceneManager->FixedUpdate(mFixedUpdateTime);
		}

		sf::Event event;
		mSceneManager->InputProcess(mRenderWindow, event);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mSceneManager->Draw(mRenderWindow);

		mRenderWindow->display();

		HandleEvents(event);

		mTimer.Update();
	}
}


void LaiEngine::Engine::SetSimulationTime(const float t)
{
	mFixedUpdateTime = t;
}

bool LaiEngine::Engine::InitGL(const std::string& title)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	try
	{
		sf::String sf_title(title.c_str());
		mRenderWindow->create({ 800, 800 }, sf_title, sf::Style::Close, settings);

		if (!gladLoadGL())
		{
			throw std::runtime_error("Failed to load OpenGL");
		}
	}
	catch (std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
		return false;
	}


	glViewport(0, 0, mRenderWindow->getSize().x, mRenderWindow->getSize().y);

	glEnable(GL_DEPTH_TEST);

	return true;
}

