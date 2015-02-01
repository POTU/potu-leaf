#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

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
    void init(Layer* layer, b2World* world);
    void update(float delta);
    void moveInResponseToTouchAt(Vec2 coordinates);
    void changeEnergy(float amount);
    bool isDead();
    Node* mRoot;

	Sprite* getSprite();

private:
	b2Body* mBody;
    Sprite* mSprite;
    void updateLeafColor();
	void addForceToQueue(b2Vec2 forceVec, float timeToTrigger);
	std::vector<ForceNode*> mForceNodes;
    float maxEnergy;
    float currentEnergy;
    bool deathHandled;
};

#endif