#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <vector>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "WorldTile.h"

class TileableWorld
{
public:
	TileableWorld();
	~TileableWorld();
	void init(cocos2d::Layer* layer, b2World* world, cocos2d::Layer* bgLayer_);
	void update(float delta);
    b2World* physWorld;

private:
	cocos2d::Layer* gameLayer;
	cocos2d::Layer* bgLayer;
	float mOffset;
	int mTileIndex;
	void generateTiles();
	std::vector<WorldTile*> mTiles;
	WorldTile* mVisibleTiles[3];
	void stepTiles();
};


#endif