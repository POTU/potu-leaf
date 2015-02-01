#include "Rock.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "standards.h"
#include "Helpers.h"
#include "GameManager.h"

using namespace cocos2d;

Rock::Rock() { }
Rock::~Rock() { }

void Rock::init(GameManager* gameManager, float x, float y)
{
    auto dir = Director::getInstance();
    auto screen = dir->getWinSize();
    
    b2BodyDef bd;
    bd.position.Set(x/PTM_RATIO, y/PTM_RATIO);
	bd.type = b2BodyType::b2_staticBody;
    bd.fixedRotation = true;
    mBody = gameManager->physWorld->CreateBody(&bd);
    
    b2CircleShape shape;
    shape.m_radius = 0.15f;
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 0.75f;
    mBody->CreateFixture(&fd);
    
    mRoot = Node::create();
    mRoot->setPosition(Vec2(0, 0));
    gameManager->gameLayer->addChild(mRoot);
    
	mSprite = Sprite::createWithSpriteFrameName("kivi1.png");
    mSprite->setPosition(Vec2(0, 0));
    mRoot->addChild(mSprite);

	spawnX = x;
	spawnY = y;
}

void Rock::update(float delta, float x, float y)
{
    if (mBody && mBody->IsActive())
    {
		b2Vec2 pos;
		pos.x = (x + spawnX)/PTM_RATIO;
		pos.y = (y + spawnY)/PTM_RATIO;
		mBody->SetTransform(pos, 0);
        mRoot->setPosition(Vec2(pos.x*PTM_RATIO, pos.y*PTM_RATIO));
    }
}

void Rock::setActive(bool isActive)
{
    if (isActive) {
        CCLOG("ACTIVATE ROCK");
        auto dir = Director::getInstance();
        auto screen = dir->getWinSize();
        mBody->SetTransform(b2Vec2(screen.width/2/PTM_RATIO, screen.height/2/PTM_RATIO), 0.0f);
        mBody->SetActive(true);
    }
    else {
        CCLOG("DEACTIVATE ROCK");
        mBody->SetActive(false);
    }
}