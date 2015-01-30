#include "TileableWorld.h"


TileableWorld::TileableWorld()
{
}
TileableWorld::~TileableWorld()
{
}

void TileableWorld::init(cocos2d::Layer* layer, b2World* world)
{
	gameLayer = layer;
	physWorld = world;
}