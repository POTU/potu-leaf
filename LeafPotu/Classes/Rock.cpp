#include "Rock.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "standards.h"
#include "Helpers.h"

USING_NS_CC;

Rock::Rock() { }
Rock::~Rock() { }

void Rock::init(cocos2d::Node* parentNode, b2World* physicWorld)
{
    auto dir = Director::getInstance();
    auto screen = dir->getWinSize();
    
    b2BodyDef bd;
    //bd.position = b2Vec2(0, 0);
    bd.position.Set(screen.width/2/PTM_RATIO, screen.height/2/PTM_RATIO);
    bd.type = b2BodyType::b2_staticBody;
    bd.fixedRotation = true;
    mBody = physicWorld->CreateBody(&bd);
    
    b2CircleShape shape;
    shape.m_radius = 0.15f;
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 0.75f;
    mBody->CreateFixture(&fd);
    
    mRoot = Node::create();
    mRoot->setPosition(Vec2(0, 0));
    parentNode->addChild(mRoot);
    
    mSprite = Sprite::create("HelloWorld.png");
    mSprite->setPosition(Vec2(0, 0));
    mSprite->setScale(0.4f, 0.4f);
    mRoot->addChild(mSprite);
    
}

void Rock::update(float delta)
{
    if (mBody && mRoot)
    {
        auto xx = mBody->GetLinearVelocity();
        mBody->SetLinearVelocity(b2Vec2(xx.x, xx.y - 0.01f));
    }
}

void Rock::setActive(bool isActive)
{
    if (isActive) {
        mBody->SetActive(true);
    }
    else {
        mBody->SetActive(false);
    }
}