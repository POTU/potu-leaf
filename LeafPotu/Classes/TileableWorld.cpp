#include "TileableWorld.h"
#include "Player.h"

USING_NS_CC;

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
    auto p = new Player();
    p->init(layer, world);
}
