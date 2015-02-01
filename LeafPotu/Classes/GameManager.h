#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "standards.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Player.h"

using namespace cocos2d;

class GameManager
{
public:
	GameManager();
	~GameManager();
	void init(Layer* gameLayer, Layer* bgLayer, b2World* physWorld);
	void InputCoordinates(cocos2d::Vec2 coordinates);
	void PauseGame(bool Pause);
	void MuteGame();
	void ResetGame();
    void GameOver();
	void update(float delta);
    Layer* gameLayer;
    Layer* bgLayer;
    b2World* physWorld;
    Player* player;
    
private:
	bool Paused;
	bool Muted;
	bool isGameOver;
	float gameOverTimer;

	void exitToMainMenu();
};
#endif