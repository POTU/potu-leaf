#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "standards.h"
#include "cocos2d.h"
#include "TileableWorld.h"
#include "Box2D/Box2D.h"
#include "Player.h"


class GameManager
{
public:
	GameManager();
	~GameManager();

	void init(cocos2d::Layer* gameLayer, TileableWorld* tileableWorld, b2World* physWorld);
	void InputCoordinates(cocos2d::Vec2 coordinates);
	void PauseGame();
	void MuteGame();
	void ResetGame();
	void EndGame();
	void update(float delta);
    
private:
	cocos2d::Layer* gameLayer;
	TileableWorld* tileableWorld;
	b2World* physWorld;
    Player* player;
	bool Paused;
	bool Muted;
};
#endif