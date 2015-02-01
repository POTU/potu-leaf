#include "WaterStrider.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "standards.h"
#include "Helpers.h"
#include "GameManager.h"

using namespace cocos2d;

WaterStrider::WaterStrider() { }
WaterStrider::~WaterStrider() { }

void WaterStrider::init(GameManager* gameManager, float x, float y)
{
    this->gameManager = gameManager;
    
    auto dir = Director::getInstance();
    auto screen = dir->getWinSize();
    
    mRoot = Node::create();
    mRoot->setPosition(Vec2(0, 0));
    gameManager->gameLayer->addChild(mRoot);
    
    mSprite = Sprite::create("HelloWorld.png");
    mSprite->setPosition(Vec2(0, 0));
    mSprite->setScale(0.5f, 0.5f);
    mRoot->addChild(mSprite);
    
    spawnX = x;
    spawnY = y;
}

void WaterStrider::update(float delta, float x, float y)
{
    if (mRoot && mRoot->isVisible())
    {
        b2Vec2 boxPos;
        boxPos.x = (x + spawnX)/PTM_RATIO;
        boxPos.y = (y + spawnY)/PTM_RATIO;
        Vec2 cocoPos = Vec2(boxPos.x*PTM_RATIO, boxPos.y*PTM_RATIO);;
        mRoot->setPosition(cocoPos);
        
        auto player = this->gameManager->player;
        auto distanceToPlayer = player->mRoot->getPosition().distance(cocoPos);
        if (distanceToPlayer < 50) {
            player->changeEnergy(-10.0f);
            mRoot->setVisible(false);
        }
    }
}

void WaterStrider::setActive(bool isActive)
{
    if (isActive) {
        CCLOG("ACTIVATE WATER STRIDER");
        mRoot->setVisible(true);
    }
    else {
        CCLOG("DEACTIVATE WATER STRIDER");
        mRoot->setVisible(false);
    }
}