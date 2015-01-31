#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Player
{
public:
    Player();
    ~Player();
    void init(cocos2d::Layer* layer, b2World* world);
    void moveInResponseToTouchAt(cocos2d::Vec2 coordinates);
private:
    cocos2d::PhysicsBody* mBody; // TODO: change to box2d
    cocos2d::Sprite* mSprite;
    cocos2d::Node* mRoot;
};

#endif