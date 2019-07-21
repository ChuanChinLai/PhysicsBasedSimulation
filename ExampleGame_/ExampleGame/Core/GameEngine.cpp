#include "GameEngine.h"

#include <Scene/ExampleScene.h>

#include <iostream>

LaiEngine::GameEngine::GameEngine(const std::string & title) : Engine(title)
{

}

bool LaiEngine::GameEngine::Init()
{
	SetSimulationTime(0.002f);

	std::shared_ptr<ExampleScene> scene = std::make_shared<ExampleScene>(*mSceneManager);
	mSceneManager->SetGameScene(scene);

	return true;
}


void LaiEngine::GameEngine::Release()
{
}

void LaiEngine::GameEngine::HandleEvents(sf::Event & event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mIsGameRunning = false;
	}

	while (mRenderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mIsGameRunning = false;
		}
		else
		{
			mSceneManager->InputProcess(mRenderWindow, event);
		}
	}
}