#include "Player.h"

USING_NS_CC;

Player::Player() { }
Player::~Player() { }

void Player::init(cocos2d::Layer* layer, b2World* world)
{
    auto dir = Director::getInstance();
    auto screen = dir->getWinSize();
    
    mRoot = Node::create();
    mRoot->setPosition(0,0);
    layer->addChild(mRoot);
    
    mSprite = Sprite::create("HelloWorld.png");
    mSprite->setPosition(Vec2(screen.width / 2, screen.height / 2));
    mSprite->setScale(0.25f, 0.25f);
    
    mBody = PhysicsBody::createBox(Size(1.0f , 1.0f ), PhysicsMaterial(0.1f, 0.1f, 0.0f));
    mBody->setGravityEnable(false);
    mSprite->setPhysicsBody(mBody);
    
    mRoot->addChild(mSprite);
}

void Player::moveInResponseToTouchAt(cocos2d::Vec2 coordinates)
{
    auto maxInteractionDistance = 400.0f;
    auto distance = mRoot->getPosition().distance(coordinates);
    float distanceFactor;
    if (distance > maxInteractionDistance) {
        distanceFactor = 0.0f;
    }
    else {
        auto t = (distance / maxInteractionDistance);
        if (t > 1.0f) { t = 1.0f; }
        t = (1.0f - t);
        distanceFactor = t;
    }
    
    auto difference = coordinates - mRoot->getPosition();
    
    float distanceX = abs(difference.x);
    auto tt = (distanceX / maxInteractionDistance);
    if (tt > 1.0f) { tt = 1.0f; }
    if (tt < -1.0f) { tt = -1.0f; }
    tt = (1.0f - tt);
    auto distanceFactorX = tt;
    if (difference.x < 0) {
        distanceFactorX = -distanceFactorX;
    }
    
    float distanceY = abs(difference.y);
    auto ttt = (distanceY / maxInteractionDistance);
    if (ttt > 1.0f) { ttt = 1.0f; }
    if (ttt < -1.0f) { ttt = -1.0f; }
    ttt = (1.0f - ttt);
    auto distanceFactorY = ttt;
    if (difference.y < 0) {
        distanceFactorY = -distanceFactorY;
    }
    
    auto maxForce = 25.0f;
    auto forceX = -(maxForce * distanceFactorX * distanceFactor);
    auto forceY = -(maxForce * distanceFactorY * distanceFactor);
    
    CCLOG("Leaf push: %4.2f %4.2f", forceX, forceY);
    mSprite->getPhysicsBody()->applyImpulse(Vec2(forceX, forceY));
}