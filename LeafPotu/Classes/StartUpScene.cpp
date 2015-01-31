#include "StartUpScene.h"
#include "GameScene.h"

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
    showingStartMenu = false;
    
	int seed = (int)time(NULL);
	srand(seed);
    return true;
}

void StartUpScene::update(float delta)
{
	if (isFirstUpdate)
	{
        // Don't do anything on first update, why? Only god knows.
		isFirstUpdate = false;
		return;
	}

	if (!hasLoaded)
	{
        // Keep loading resources until we are ready to show the real title screen.
        hasLoaded = true;
        return;
	}
    
    if (showingStartMenu) {
        return;
    }
    
    auto startLbl = Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 48);
    cocos2d::Size screen = Director::getInstance()->getWinSize();
    startLbl->setPosition(Vec2(screen.width / 2, screen.height / 2));
    startLbl->setColor(cocos2d::Color3B::WHITE);
    this->addChild(startLbl);
    
    auto startLstnr = EventListenerTouchOneByOne::create();
    startLstnr->onTouchBegan = [](Touch* touch, Event* event){
        Scene* gameScene = GameScene::scene();
        Director::getInstance()->replaceScene(gameScene);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(startLstnr, startLbl);
    
    showingStartMenu = true;
}
