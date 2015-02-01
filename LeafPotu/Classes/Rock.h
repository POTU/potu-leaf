#ifndef ROCK_H
#define ROCK_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Obstacle.h"
#include "GameManager.h"

using namespace cocos2d;

class Rock : public Obstacle
{
public:
    Rock();
    ~Rock();
    virtual void init(GameManager* gameManager, float x, float y);
    virtual void update(float delta, float x, float y);
    virtual void setActive(bool isActive);
};

#endif
