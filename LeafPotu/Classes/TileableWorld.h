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
	void init(cocos2d::Layer* layer, b2World* world);

	void update(float delta);

private:
	cocos2d::Layer* gameLayer;
	b2World* physWorld;

	float mOffset;
	int mTileIndex;

	void generateTiles();
	std::vector<WorldTile*> mTiles;
	WorldTile* mVisibleTiles[3];

	void stepTiles();
};


#endif