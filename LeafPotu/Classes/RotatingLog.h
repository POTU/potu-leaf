#ifndef ROTATING_LOG_H
#define ROTATING_LOG_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Obstacle.h"
#include "GameManager.h"

using namespace cocos2d;

class RotatingLog : public Obstacle
{
public:
    RotatingLog();
    ~RotatingLog();
    virtual void init(GameManager* gameManager, float x, float y);
    virtual void update(float delta, float x, float y);
    virtual void setActive(bool isActive);
private:
    float mOffset;
};

#endif