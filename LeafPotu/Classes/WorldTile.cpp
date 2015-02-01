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
    if (tileId == 0) {
        
    }
    else {
        valids.push_back(rd::toTilePoint(Vec2(768, 3500)));
        valids.push_back(rd::toTilePoint(Vec2(768, 3000)));
        valids.push_back(rd::toTilePoint(Vec2(768, 2500)));
        valids.push_back(rd::toTilePoint(Vec2(768, 2000)));
        valids.push_back(rd::toTilePoint(Vec2(768, 1500)));
        valids.push_back(rd::toTilePoint(Vec2(768, 1000)));
        valids.push_back(rd::toTilePoint(Vec2(768, 500)));
        valids.push_back(rd::toTilePoint(Vec2(768, 0)));
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

	int randomTileValue = rd::RandInt(1,3);
    
    auto valids = getValids(randomTileValue);
    int validCount = (int)valids.size();
    std::random_shuffle(valids.begin(), valids.end());
    for (int i = 0; i < validCount; i++) {
        int oType = rd::RandInt(1, 10);
        Obstacle* o;
        if (oType <= 2) {
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
    
    /*
    auto r = new Rock();
    auto rp = rd::toTilePoint(Point(1536, 4096));
	r->init(gameManager, rp.x, rp.y);
    mObstacles.push_back(r);
    
    auto c1 = new Chlorophyll();
    c1->init(gameManager, screen.width/2.5f, screen.height/2.5f);
    mObstacles.push_back(c1);
    
    auto c2 = new Chlorophyll();
    c2->init(gameManager, screen.width/1.5f, screen.height/2.5f);
    mObstacles.push_back(c2);
    
    auto l1 = new RotatingLog();
    l1->init(gameManager, screen.width/2.5f, screen.height/1.0f);
    mObstacles.push_back(l1);
    
    auto l2 = new RotatingLog();
    l2->init(gameManager, screen.width/2.1f, screen.height/0.85f);
    mObstacles.push_back(l2);
    
    auto l3 = new RotatingLog();
    l3->init(gameManager, screen.width/3.2f, screen.height/0.80f);
    mObstacles.push_back(l3);
    
    auto w = new WaterStrider();
    w->init(gameManager, 1150, 600);
    mObstacles.push_back(w);
    */

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