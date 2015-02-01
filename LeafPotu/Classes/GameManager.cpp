#include "GameManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Player.h"
#include "Helpers.h"
#include "PauseScene.h"
#include "EndScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameManager::GameManager() { }
GameManager::~GameManager() { }

void GameManager::init(Layer* gameLayer, Layer* bgLayer, b2World* physWorld)
{
	this->gameLayer = gameLayer;
    this->bgLayer = bgLayer;
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
	isGameOver = false;
	gameOverTimer = 0;
}

void GameManager::update(float delta)
{
	if(!isGameOver) player->update(delta);
	if (player->isDead() && !isGameOver) {
        GameOver();
    }

	cocos2d::Vec2 playerPos = player->mRoot->getPosition();
	if(playerPos.y < -200 || playerPos.y > 3000)
	{
		if(!isGameOver) this->GameOver();
	}

	if(isGameOver)
	{
		gameOverTimer = gameOverTimer + delta;
		if(gameOverTimer > 2.0f) this->exitToMainMenu();
	}

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

void GameManager::GameOver()
{
    // Add cause of death to function calls and show in end screen.
    // Show end screen wiht score and cause of death.
	isGameOver = true;

	Sprite* playerSprite = player->getSprite();
	if(playerSprite)
	{
		FadeTo* fadeAction = FadeTo::create(2.0f, 30);
		ScaleTo* scaleAction = ScaleTo::create(2.0f, 0.75f);
		playerSprite->runAction(fadeAction);
		playerSprite->runAction(scaleAction);
	}
}


void GameManager::exitToMainMenu()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene* endScene = EndScene::scene();
	TransitionFade* transScene = TransitionFade::create(1.0f, endScene);
	Director::getInstance()->replaceScene(transScene);
}
