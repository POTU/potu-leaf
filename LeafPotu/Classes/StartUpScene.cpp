#include "StartUpScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GB2ShapeCache-x.h"

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
    if (!Layer::init())
    {
        return false;
    }
	this->scheduleUpdate();
	
    isFirstUpdate = true;
	hasLoaded = false;
    
	int seed = (int)time(NULL);
	srand(seed);
    return true;
}

void StartUpScene::update(float delta)
{
	if (isFirstUpdate)
	{
		isFirstUpdate = false;
		return;
	}

	if (!hasLoaded)
	{
        // Keep loading resources until we are ready to show the real title screen.
		GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("physSheet.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("envSheet1.plist");
        hasLoaded = true;
        return;
	}
    
    Scene* menuScene = MenuScene::scene();
    Director::getInstance()->replaceScene(menuScene);
}
