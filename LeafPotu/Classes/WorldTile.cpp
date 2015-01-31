#include "WorldTile.h"
#include "standards.h"
#include "Helpers.h"
#include "GB2ShapeCache-x.h"

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

void WorldTile::generate(cocos2d::Layer* layer, b2World* world)
{
	mRoot = Node::create();
	mRoot->setPosition(0,0);
	layer->addChild(mRoot);

	b2BodyDef bd;
	bd.position = b2Vec2(0,0);
	mBody = world->CreateBody(&bd);

	int randomTileValue = rd::RandInt(1,8);

	std::string tileStr = "tile" + rd::StringFromInt(randomTileValue);
	std::string spriteStr = tileStr + ".png";
	std::string shapeStr = tileStr;

	GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(mBody, shapeStr);

	Sprite* sprite = Sprite::createWithSpriteFrameName(spriteStr);
	sprite->setAnchorPoint(cocos2d::Vec2(0,0));
	mRoot->addChild(sprite);

	this->cacheToPool();
}

void WorldTile::update(float x, float y, float delta)
{
	if(mRoot) mRoot->setPosition(x,y);
	if(mBody) mBody->SetTransform(b2Vec2(x/PTM_RATIO, y/PTM_RATIO), 0);

	//Obstacle update
	std::vector<Obstacle*>::iterator it;
	for(it = mObstacles.begin(); it < mObstacles.end(); it++)
	{
		Obstacle* iObs = *it;
	}
}


void WorldTile::cacheToPool()
{
	if(mBody) mBody->SetActive(false);
	if(mRoot) mRoot->setVisible(false);
}

void WorldTile::uncacheFromPool()
{
	if(mBody) mBody->SetActive(true);
	if(mRoot) mRoot->setVisible(true);
}