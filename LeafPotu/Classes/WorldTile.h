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
	void generate(cocos2d::Layer* layer, b2World* world);

	void cacheToPool();
	void uncacheFromPool();

	bool isInCache;

private:
	b2Body* mBody;
	cocos2d::Sprite* mSprite;
	cocos2d::Node* mRoot;
	std::vector<Obstacle*> mObstacles;
};

#endif