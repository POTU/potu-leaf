#include "GameManager.h"
#include "Player.h"

using namespace cocos2d;

void GameManager::init(cocos2d::Layer* gameLayer, TileableWorld* tileableWorld, b2World* physWorld)
{
	this->gameLayer = gameLayer;
	this->tileableWorld = tileableWorld;
	this->physWorld = physWorld;

    Player *player = new Player();
    player->init(this->gameLayer, this->physWorld);
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

