#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>

#include "cocos2d.h"
#include "Box2D/Box2D.h"

struct ForceNode
{
	b2Vec2 force;
	float timer;
};

class Player
{
public:
    Player();
    ~Player();
    void init(cocos2d::Layer* layer, b2World* world);
    void update(float delta);
    void moveInResponseToTouchAt(cocos2d::Vec2 coordinates);
private:
	b2Body* mBody;
    cocos2d::Sprite* mSprite;
    cocos2d::Node* mRoot;

	void addForceToQueue(b2Vec2 forceVec, float timeToTrigger);
	std::vector<ForceNode*> mForceNodes;
};

#endif