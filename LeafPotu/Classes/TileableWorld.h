#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <vector>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class TileableWorld
{
public:
	TileableWorld();
	~TileableWorld();
	void init(cocos2d::Layer* layer, b2World* world);

private:
	cocos2d::Layer* gameLayer;
	b2World* physWorld;
};


#endif