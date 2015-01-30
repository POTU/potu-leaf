#include "StartUpScene.h"


USING_NS_CC;

Scene* StartUpScene::scene()
{
    Scene *scene = Scene::create();
    
    StartUpScene *layer = StartUpScene::create();

    scene->addChild(layer);

    return scene;
}

bool StartUpScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	this->scheduleUpdate();

	cocos2d::Size screen = Director::getInstance()->getWinSize();

	skip = true;
	hasLoaded = false;

	int seed = time(NULL);
	srand(seed);

    return true;
}

void StartUpScene::update(float delta)
{
	if(skip)
	{
		skip = false;
		return;
	}

	if(hasLoaded)
	{

	}
	else
	{
		hasLoaded = true;
	}
}
