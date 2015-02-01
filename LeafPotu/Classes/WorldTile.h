#ifndef WORLD_TILE_H
#define WORLD_TILE_H

#include "standards.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Obstacle.h"
#include "GameManager.h"

using namespace cocos2d;

class WorldTile
{
public:
	WorldTile();
	~WorldTile();
	void update(float x, float y, float delta);
	void generate(GameManager* gameManager);
	void cacheToPool();
	void uncacheFromPool();
	bool isInCache;
private:
	b2Body* mBody;
	Sprite* mSprite;
	Node* mRoot;
	Node* mBgRoot;
	Sprite* mWaterWave1;
	std::vector<Obstacle*> mObstacles;
    std::vector<Vec2> getValids(int tileId);
};

#endif