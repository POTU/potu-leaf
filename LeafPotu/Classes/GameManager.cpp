#include "GameManager.h"

using namespace cocos2d;

void GameManager::init(cocos2d::Layer* layer, TileableWorld* world, b2Body* Body)
{
	gameLayer = layer;
	tileableWorld = world;
	boxBody = Body;
}

void GameManager::InputCoordinates(Vec2 Coordinates)
{
	
}

void GameManager::PauseGame()
{
	if (Paused == false)
	{
		Paused = true;
		// Pause Game
	}
	else
	{
		Paused = false;
		// Un-pause Game
	}
}

void GameManager::EndGame()
{

}

