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

void WorldTile::generate(cocos2d::Layer* layer, b2World* world)
{
	mRoot = Node::create();
	mRoot->setPosition(0,0);
	layer->addChild(mRoot);

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

	this->cacheToPool();
}

void WorldTile::update(float x, float y, float delta)
{
	cocos2d::Size screen = Director::getInstance()->getWinSize();

	if (mRoot) mRoot->setPosition(x+(screen.width/2),y);
	if (mBody) mBody->SetTransform(b2Vec2((x+(screen.width/2))/PTM_RATIO, y/PTM_RATIO), 0);

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
	if (mBody) mBody->SetActive(true);
	if (mRoot) mRoot->setVisible(true);
    std::vector<Obstacle*>::iterator it;
    for (it = mObstacles.begin(); it < mObstacles.end(); it++)
    {
        Obstacle* iObs = *it;
        iObs->setActive(true);
    }
}