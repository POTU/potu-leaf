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
    virtual void init(cocos2d::Layer* gameLayer, b2World* physicWorld, float x, float y);
    virtual void update(float delta, float x, float y);
    virtual void setActive(bool isActive);

private:
	float mX;
	float mY;
};

#endif
