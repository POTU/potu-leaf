#include "RotatingLog.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "standards.h"
#include "Helpers.h"
#include "GameManager.h"

using namespace cocos2d;

RotatingLog::RotatingLog() { }
RotatingLog::~RotatingLog() { }

void RotatingLog::init(GameManager* gameManager, float x, float y)
{
    auto dir = Director::getInstance();
    auto screen = dir->getWinSize();
    
    b2BodyDef bd;
    bd.position.Set(x/PTM_RATIO, y/PTM_RATIO);
    bd.type = b2BodyType::b2_staticBody;
    bd.fixedRotation = true;
    mBody = gameManager->physWorld->CreateBody(&bd);
    
    b2PolygonShape shape;
    shape.SetAsBox(0.3f, 0.055f);
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 0.75f;
    mBody->CreateFixture(&fd);
    
    mRoot = Node::create();
    mRoot->setPosition(Vec2(0, 0));
    gameManager->gameLayer->addChild(mRoot);
    
    mSprite = Sprite::create("HelloWorld.png");
    mSprite->setPosition(Vec2(0, 0));
    mSprite->setScale(0.6f, 0.15f);
    mRoot->addChild(mSprite);
    
    spawnX = x;
    spawnY = y;
    mOffset = 0;
}

void RotatingLog::update(float delta, float x, float y)
{
    if (mBody && mBody->IsActive())
    {
        mOffset -= 2.0f;
        b2Vec2 boxPos;
        boxPos.x = (x + spawnX)/PTM_RATIO;
        boxPos.y = (y + spawnY + mOffset)/PTM_RATIO;
        mBody->SetTransform(boxPos, mBody->GetAngle() + 0.01f);
        Vec2 cocoPos = Vec2(boxPos.x*PTM_RATIO, boxPos.y*PTM_RATIO);
        mRoot->setPosition(cocoPos);
        mRoot->setRotation(-rd::RadToDeg(mBody->GetAngle()));
    }
}

void RotatingLog::setActive(bool isActive)
{
    if (isActive) {
        CCLOG("ACTIVATE ROTATING LOG");
        mOffset = 0;
        mBody->SetActive(true);
    }
    else {
        CCLOG("DEACTIVATE ROTATING LOG");
        mBody->SetActive(false);
    }
}