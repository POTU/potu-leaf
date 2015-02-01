#include "WorldTile.h"
#include "standards.h"
#include "Helpers.h"
#include "GB2ShapeCache-x.h"
#include "Obstacle.h"
#include "Rock.h"
#include "Chlorophyll.h"
#include "GameManager.h"

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

void WorldTile::generate(GameManager* gameManager)
{
	Size screen = Director::getInstance()->getWinSize();

	mRoot = Node::create();
	mRoot->setPosition(0,0);
	gameManager->gameLayer->addChild(mRoot);

	mBgRoot = Node::create();
	mBgRoot->setPosition(0,0);
	gameManager->bgLayer->addChild(mBgRoot);

	b2BodyDef bd;
	bd.position = b2Vec2(0,0);
	mBody = gameManager->physWorld->CreateBody(&bd);

	int randomTileValue = rd::RandInt(1,2);
	randomTileValue = 1;
    
    auto r = new Rock();
	r->init(gameManager, screen.width/2, screen.height/2);
    mObstacles.push_back(r);
    
    auto c1 = new Chlorophyll();
    c1->init(gameManager, screen.width/2.5f, screen.height/2.5f);
    mObstacles.push_back(c1);
    
    auto c2 = new Chlorophyll();
    c2->init(gameManager, screen.width/1.5f, screen.height/2.5f);
    mObstacles.push_back(c2);

	std::string tileStr = "Tile" + rd::StringFromInt(randomTileValue);
	std::string spriteStr = tileStr + ".png";
	std::string shapeStr = tileStr;

	GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(mBody, shapeStr);

	Sprite* sprite = Sprite::createWithSpriteFrameName(spriteStr);
	sprite->setScale(2.0f);
	mRoot->addChild(sprite);

	mWaterWave1 = Sprite::createWithSpriteFrameName("waterAlpha1.png");
	mWaterWave1->setScale(2.0f, 3.511f);
	mWaterWave1->setOpacity(180);
	mBgRoot->addChild(mWaterWave1);

	this->cacheToPool();
}

void WorldTile::update(float x, float y, float delta)
{
	cocos2d::Size screen = Director::getInstance()->getWinSize();

	if (mRoot) mRoot->setPosition(x+(screen.width/2),y);
	if (mBgRoot) mBgRoot->setPosition(x+(screen.width/2),y);
	if (mBody) mBody->SetTransform(b2Vec2((x+(screen.width/2))/PTM_RATIO, y/PTM_RATIO), 0);

	std::vector<Obstacle*>::iterator it;
	for (it = mObstacles.begin(); it < mObstacles.end(); it++)
	{
		Obstacle* iObs = *it;
        iObs->update(delta, x, y);
	}
}


void WorldTile::cacheToPool()
{
	if (mBgRoot) mBgRoot->setVisible(false);
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
	if (mBgRoot) mBgRoot->setVisible(true);
	if (mBody) mBody->SetActive(true);
	if (mRoot) mRoot->setVisible(true);
    
    std::vector<Obstacle*>::iterator it;
    for (it = mObstacles.begin(); it < mObstacles.end(); it++)
    {
        Obstacle* iObs = *it;
        iObs->setActive(true);
    }

}