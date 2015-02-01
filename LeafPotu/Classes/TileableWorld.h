#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <vector>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "WorldTile.h"

using namespace cocos2d;

class TileableWorld
{
public:
	TileableWorld();
	~TileableWorld();
	void init(Layer* gameLayer, b2World* physWorld, Layer* bgLayer);
	void update(float delta);
    b2World* physWorld;

private:
	Layer* gameLayer;
	Layer* bgLayer;
	float mOffset;
	int mTileIndex;
	void generateTiles();
	std::vector<WorldTile*> mTiles;
	WorldTile* mVisibleTiles[3];
	void stepTiles();
};


#endif