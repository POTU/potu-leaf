#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameManager.h"

using namespace cocos2d;

class Obstacle
{
public:
    Obstacle();
    virtual ~Obstacle() = 0;
    virtual void init(GameManager* gameManager, float x, float y) = 0;
    virtual void update(float delta, float x, float y) = 0;
    virtual void setActive(bool isActive) = 0;
protected:
    GameManager* gameManager;
    b2Body* mBody;
    Sprite* mSprite;
    Node* mRoot;
    float spawnX;
    float spawnY;
};

#endif