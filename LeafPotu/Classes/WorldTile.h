#ifndef WORLD_TILE_H
#define WORLD_TILE_H

#include "standards.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Obstacle.h"

class WorldTile
{
public:
	WorldTile();
	~WorldTile();

	void update(float x, float y, float delta);
	void generate(cocos2d::Layer* layer, b2World* world, cocos2d::Layer* bgLayer);

	void cacheToPool();
	void uncacheFromPool();

	bool isInCache;

private:
	b2Body* mBody;
	cocos2d::Sprite* mSprite;
	cocos2d::Node* mRoot;

	cocos2d::Node* mBgRoot;

	cocos2d::Sprite* mWaterWave1;
	cocos2d::Sprite* mWaterWave2;
	cocos2d::Sprite* mWaterWave3;

	std::vector<Obstacle*> mObstacles;
};

#endif