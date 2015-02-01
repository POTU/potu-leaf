#include "WorldTile.h"
#include "standards.h"
#include "Helpers.h"
#include "GB2ShapeCache-x.h"
#include "Obstacle.h"
#include "Rock.h"
#include "Chlorophyll.h"
#include "RotatingLog.h"
#include "WaterStrider.h"
#include "GameManager.h"
#include <algorithm>

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

std::vector<Vec2> WorldTile::getValids(int tileId) {
    std::vector<Vec2> valids;
    // Order: from top to bottom of on the tile (y coordinate)
    if (tileId == 1) {
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(430, 410)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(310, 900)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(440, 1210)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(300, 1460)));
    }
    else if (tileId == 2) {
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(430, 410)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(310, 900)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(440, 1600)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(300, 1600)));
    }
    else if (tileId == 3) {
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(270, 150)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(280, 340)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(420, 360)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(350, 900)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(440, 1210)));
        valids.push_back(rd::photoshopPixeltoTilePixel(Vec2(300, 1560)));
    }
    return valids;
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

	int randomTileValue = rd::RandInt(1, 3);
    
    auto valids = getValids(randomTileValue);
    int validCount = (int)valids.size();
    std::random_shuffle(valids.begin(), valids.end());
    for (int i = 0; i < validCount; i++) {
        int oType = rd::RandInt(1, 10);
        Obstacle* o;
        if (oType <= 1) {
            o = new RotatingLog();
        }
        else if (oType <= 6) {
            o = new Rock();
        }
        else {
            o = new Chlorophyll();
        }
        o->init(gameManager, valids[i].x, valids[i].y);
        mObstacles.push_back(o);
    }

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