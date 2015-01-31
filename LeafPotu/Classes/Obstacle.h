#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Obstacle
{
public:
    Obstacle();
    ~Obstacle();
    virtual void init(cocos2d::Layer* gameLayer, b2World* physicWorld, float x, float y) = 0;
    virtual void update(float delta, float x, float y) = 0;
    virtual void setActive(bool isActive) = 0;
protected:
    b2Body* mBody;
    cocos2d::Sprite* mSprite;
    cocos2d::Node* mRoot;
};

#endif