#include "Player.h"
#include "standards.h"
#include "Helpers.h"

USING_NS_CC;

Player::Player() { }
Player::~Player() 
{
	std::vector<ForceNode*>::iterator it;
	for(it = mForceNodes.begin(); it < mForceNodes.end(); it++)
	{
		ForceNode* iNode = *it;
		delete iNode;
	}
}

void Player::init(cocos2d::Layer* layer, b2World* world)
{
    auto dir = Director::getInstance();
    auto screen = dir->getWinSize();
    
    b2BodyDef bd;
    bd.position = b2Vec2(screen.width/2/PTM_RATIO, screen.height/2/PTM_RATIO);
    bd.type = b2BodyType::b2_dynamicBody;
    bd.linearDamping = 0.95f;
    bd.angularDamping = 0.5f;
    bd.fixedRotation = false;
    mBody = world->CreateBody(&bd);
    
    b2CircleShape shape;
    shape.m_radius = 0.15f;
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.restitution = 0.9f;
    fd.density = 0.75f;
    fd.friction = 0.5f;
    mBody->CreateFixture(&fd);
    
    mRoot = Node::create();
    mRoot->setPosition(Vec2(mBody->GetPosition().x*PTM_RATIO, mBody->GetPosition().y*PTM_RATIO));
    layer->addChild(mRoot);
    
	mSprite = Sprite::createWithSpriteFrameName("leaf.png");
    mSprite->setPosition(Vec2(0, 0));
    mRoot->addChild(mSprite);
}

void Player::update(float delta)
{
    auto velocity = mBody->GetLinearVelocity();
    mBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y - 0.01f));
    if (mRoot)
    {
        auto pos = mBody->GetPosition();
        mRoot->setPosition(pos.x*PTM_RATIO, pos.y*PTM_RATIO);
        mRoot->setRotation(-rd::RadToDeg(mBody->GetAngle()));
    }

	// Update force timers
	if (!mForceNodes.empty())
	{
		std::vector<ForceNode*>::iterator it;
		for(it = mForceNodes.begin(); it < mForceNodes.end(); it++)
		{
			ForceNode* iNode = *it;
			iNode->timer = iNode->timer - delta;
		}
	}

	// Update force triggers
	if (!mForceNodes.empty())
	{
		std::vector<ForceNode*>::iterator it;
		for(it = mForceNodes.begin(); it < mForceNodes.end(); it++)
		{
			ForceNode* iNode = *it;
			if(iNode->timer < 0)
			{
				mBody->ApplyForceToCenter(iNode->force, true);
				mForceNodes.erase(it);
				delete iNode;
				break;
			}
		}
	}
}

void Player::moveInResponseToTouchAt(cocos2d::Vec2 coordinates)
{
    auto maxInteractionDistance = 600.0f;
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
    
    auto maxForceX = 5.0f;
    auto maxForceY = 5.0f;
    auto forceX = -(maxForceX * distanceFactorX * distanceFactor);
    auto forceY = -(maxForceY * distanceFactorY * distanceFactor);

    float maxTriggerTime = 1.0f;
    float triggerTime;
    if (distanceFactor > 0.8f) {
        triggerTime = 0.0f;
    }
    else {
        triggerTime = (maxTriggerTime * (1.0f - distanceFactor));
    }
	this->addForceToQueue(b2Vec2(forceX, forceY), triggerTime);
    
    CCLOG("Ripple: x = %4.2f y = %4.2f t = %4.2f", forceX, forceY, triggerTime);
    
    int torqueSign = 1;
    if (difference.x < 0) {
        torqueSign = -1;
    }
    mBody->ApplyTorque(0.01f * torqueSign, true);
}

void Player::addForceToQueue(b2Vec2 forceVec, float timeToTrigger)
{
	ForceNode* newForceNode = new ForceNode();
	newForceNode->timer = timeToTrigger;
	newForceNode->force = forceVec;

	mForceNodes.push_back(newForceNode);
}