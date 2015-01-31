#ifndef GAMEMANAGER
#define GAMEMANAGER

#include "standards.h"
#include "cocos2d.h"
#include "TileableWorld.h"
#include "Box2D/Box2D.h"

class GameManager
{
public:
	void init(cocos2d::Layer* layer, TileableWorld* world, b2Body* Body);
	void InputCoordinates(Vec2 Coordinates);
	void PauseGame();
	void EndGame();

	int Score;


private:
	cocos2d::Layer* gameLayer;
	TileableWorld* tileableWorld;
	b2Body* boxBody;
	bool Paused;
};
#endif