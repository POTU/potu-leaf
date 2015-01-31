#include "TileableWorld.h"

USING_NS_CC;

TileableWorld::TileableWorld()
{
}

TileableWorld::~TileableWorld()
{
}

void TileableWorld::init(cocos2d::Layer* layer, b2World* world)
{
	gameLayer = layer;
	physWorld = world;
    doStuff();
}

void TileableWorld::doStuff()
{
    auto dir = Director::getInstance();
    auto sprite = Sprite::create("HelloWorld.png");
    auto screen = dir->getWinSize();
    sprite->setPosition(Vec2(screen.width / 2, screen.height / 2));
    sprite->setScale(0.25f, 0.25f);
    
    auto body = PhysicsBody::createBox(Size(1.0f , 1.0f ), PhysicsMaterial(0.1f, 0.1f, 0.0f));
    body->setGravityEnable(false);
    sprite->setPhysicsBody(body);
    
    gameLayer->addChild(sprite);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event){
        auto node = event->getCurrentTarget(); // TODO: Fix, not the right way to pass this.
        
        auto maxInteractionDistance = 400.0f;
        auto distance = node->getPosition().distance(touch->getLocation());
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
        
        auto difference = touch->getLocation() - node->getPosition();
        
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
        node->getPhysicsBody()->applyImpulse(Vec2(forceX, forceY));
        
        return true;
    };
    listener->setSwallowTouches(true);
    dir->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
}