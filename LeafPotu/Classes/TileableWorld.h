#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <vector>
#include "GameManager.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "WorldTile.h"

class TileableWorld
{
public:
	TileableWorld();
	~TileableWorld();
	void init(GameManager* gameManager);
	void update(float delta);
private:
    GameManager* gameManager;
	float mOffset;
	int mTileIndex;
	void generateTiles();
	std::vector<WorldTile*> mTiles;
	WorldTile* mVisibleTiles[3];
	void stepTiles();
};


#endif