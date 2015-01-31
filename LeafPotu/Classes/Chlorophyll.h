#ifndef CHLOROPHYLL_H
#define CHLOROPHYLL_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Obstacle.h"

using namespace cocos2d;

class Chlorophyll : public Obstacle
{
public:
    Chlorophyll();
    ~Chlorophyll();
    virtual void init(Layer* gameLayer, b2World* physicWorld, float x, float y);
    virtual void update(float delta, float x, float y);
    virtual void setActive(bool isActive);
};

#endif
