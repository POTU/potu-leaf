#include "WorldTile.h"
#include "standards.h"
#include "Helpers.h"
#include "GB2ShapeCache-x.h"
#include "Obstacle.h"
#include "Rock.h"

using namespace cocos2d;

WorldTile::WorldTile()
{
	isInCache = true;
	mBody = NULL;
	mRoot = NULL;
	mSprite = NULL;
}

WorldTile::~WorldTile()
{
	std::vector<Obstacle*>::iterator it;
	for(it = mObstacles.begin(); it < mObstacles.end(); it++)
	{
		Obstacle* iObs = *it;
		delete iObs;
	}
}

void WorldTile::generate(cocos2d::Layer* layer, b2World* world, cocos2d::Layer* bgLayer)
{
	mRoot = Node::create();
	mRoot->setPosition(0,0);
	layer->addChild(mRoot);

	mBgRoot = Node::create();
	mBgRoot->setPosition(0,0);
	bgLayer->addChild(mBgRoot);

	b2BodyDef bd;
	bd.position = b2Vec2(0,0);
	mBody = world->CreateBody(&bd);

	int randomTileValue = rd::RandInt(1,2);
	randomTileValue = 1;
    
    auto r = new Rock();
    r->init(layer, world);
    mObstacles.push_back(r);

	std::string tileStr = "Tile" + rd::StringFromInt(randomTileValue);
	std::string spriteStr = tileStr + ".png";
	std::string shapeStr = tileStr;

	GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(mBody, shapeStr);

	Sprite* sprite = Sprite::createWithSpriteFrameName(spriteStr);
	sprite->setScale(2.0f);
	mRoot->addChild(sprite);

	Size screen = Director::getInstance()->getWinSize();

	mWaterWave1 = Sprite::createWithSpriteFrameName("waterAlpha1.png");
	mWaterWave1->setScale(2.0f, 3.511f);
	mBgRoot->addChild(mWaterWave1);

	mWaterWave2 = Sprite::createWithSpriteFrameName("waterAlpha2.png");
	mWaterWave2->setScale(2.0f, 3.511f);
	mWaterWave2->setOpacity(0);
	mBgRoot->addChild(mWaterWave2);

	mWaterWave3 = Sprite::createWithSpriteFrameName("waterAlpha3.png");
	mWaterWave3->setScale(2.0f, 3.511f);
	mWaterWave3->setOpacity(0);
	mBgRoot->addChild(mWaterWave3);

	float fadeTime = 2.0f;
	int maxOpa = 170;
	Sequence* water1Seq = Sequence::create(FadeTo::create(fadeTime, 0), DelayTime::create(fadeTime), FadeTo::create(fadeTime, maxOpa), NULL);
	Sequence* water2Seq = Sequence::create(FadeTo::create(fadeTime, maxOpa), FadeTo::create(fadeTime, 0), DelayTime::create(fadeTime), NULL);
	Sequence* water3Seq = Sequence::create(DelayTime::create(fadeTime), FadeTo::create(fadeTime, maxOpa), FadeTo::create(fadeTime, 0), NULL);
	
	mWaterWave1->runAction(RepeatForever::create(water1Seq));
	mWaterWave2->runAction(RepeatForever::create(water2Seq));
	mWaterWave3->runAction(RepeatForever::create(water3Seq));

	this->cacheToPool();
}

void WorldTile::update(float x, float y, float delta)
{
	cocos2d::Size screen = Director::getInstance()->getWinSize();


	if(mRoot) mRoot->setPosition(x+(screen.width/2),y);
	if(mBgRoot) mBgRoot->setPosition(x+(screen.width/2),y);
	if(mBody) mBody->SetTransform(b2Vec2((x+(screen.width/2))/PTM_RATIO, y/PTM_RATIO), 0);

	// Obstacle update
	std::vector<Obstacle*>::iterator it;
	for (it = mObstacles.begin(); it < mObstacles.end(); it++)
	{
		Obstacle* iObs = *it;
        iObs->update(delta);
	}
}


void WorldTile::cacheToPool()
{

	if(mBgRoot) mBgRoot->setVisible(false);

	if (mBody) mBody->SetActive(false);
	if (mRoot) mRoot->setVisible(false);
    std::vector<Obstacle*>::iterator it;
    for (it = mObstacles.begin(); it < mObstacles.end(); it++)
    {
        Obstacle* iObs = *it;
        iObs->setActive(false);
    }

}

void WorldTile::uncacheFromPool()
{


	if(mBgRoot) mBgRoot->setVisible(true);

	if (mBody) mBody->SetActive(true);
	if (mRoot) mRoot->setVisible(true);
    std::vector<Obstacle*>::iterator it;
    for (it = mObstacles.begin(); it < mObstacles.end(); it++)
    {
        Obstacle* iObs = *it;
        iObs->setActive(true);
    }

}