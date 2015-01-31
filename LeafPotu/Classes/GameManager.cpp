#include "GameManager.h"
#include "Player.h"

using namespace cocos2d;


GameManager::GameManager()
{
}
GameManager::~GameManager()
{
	std::vector<ForceNode*>::iterator it;
	for(it = mForceNodes.begin(); it < mForceNodes.end(); it++)
	{
		ForceNode* iNode = *it;
		delete iNode;
	}
}


void GameManager::init(cocos2d::Layer* gameLayer, TileableWorld* tileableWorld, b2World* physWorld)
{
	this->gameLayer = gameLayer;
	this->tileableWorld = tileableWorld;
	this->physWorld = physWorld;

    player = new Player();
    player->init(this->gameLayer, this->physWorld);
}

void GameManager::update(float delta)
{
    player->update(delta);
	
}

void GameManager::InputCoordinates(Vec2 coordinates)
{
	// If hits water, apply force to player.
    player->moveInResponseToTouchAt(coordinates);
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

