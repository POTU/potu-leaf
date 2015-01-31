#ifndef ROCK_H
#define ROCK_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Obstacle.h"

class Rock : public Obstacle
{
public:
    Rock();
    ~Rock();
    virtual void init(cocos2d::Node* parentNode, b2World* physicWorld);
    virtual void update(float delta);
    virtual void setActive(bool isActive);
};

#endif
