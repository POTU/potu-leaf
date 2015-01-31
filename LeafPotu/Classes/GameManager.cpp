#include "GameManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Player.h"
#include "Helpers.h"
#include "PauseScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameManager::GameManager() { }
GameManager::~GameManager() { }

void GameManager::init(cocos2d::Layer* gameLayer, TileableWorld* tileableWorld, b2World* physWorld)
{
	this->gameLayer = gameLayer;
	this->tileableWorld = tileableWorld;
	this->physWorld = physWorld;
    
    Muted = false;
	Paused = false;
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio/taustaSolina.mp3", true);
	if (SimpleAudioEngine::getInstance()->getEffectsVolume() == 0.0f)
	{
        MuteGame();
	}
    SimpleAudioEngine::getInstance()->playEffect("Audio/start.mp3");
    
    player = new Player();
    player->init(this->gameLayer, this->physWorld);
}

void GameManager::update(float delta)
{
    player->update(delta);
	
}

void GameManager::InputCoordinates(Vec2 coordinates)
{
    player->moveInResponseToTouchAt(coordinates);
}


void GameManager::PauseGame(bool Pause)
{
	if (Pause == true)
	{
		Paused = true;
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		Director::getInstance()->pushScene(PauseScene::scene());
	}
	else
	{
		Paused = false;
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->popScene();
	}
}

void GameManager::MuteGame()
{
	if (Muted == true)
	{
		Muted = false;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
        SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
	}
	else
	{
		Muted = true;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0);
		SimpleAudioEngine::getInstance()->setEffectsVolume(0.0);
	}
}

void GameManager::ResetGame()
{
	Director::getInstance()->replaceScene(GameScene::scene());
}

void GameManager::EndGame()
{

}

