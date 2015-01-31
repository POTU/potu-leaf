#include "GameManager.h"
#include "Player.h"

using namespace cocos2d;

void GameManager::init(cocos2d::Layer* layer, TileableWorld* world, b2Body* Body)
{
	gameLayer = layer;
	tileableWorld = world;
	boxBody = Body;
    
    CCLOG("DONE!");
    Player *player = new Player();
    player->init(layer, tileableWorld->physWorld);
}

void GameManager::InputCoordinates(Vec2 coordinates)
{
	// If hits water, apply force to player.
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

