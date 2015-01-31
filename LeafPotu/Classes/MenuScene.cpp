#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;

Scene* MenuScene::scene()
{
	Scene *scene = Scene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Node* uiNode = CSLoader::createNode("");
	this->addChild(uiNode);
	return true;
}


// BTN_play
// BTN_mute
// BTN_exit
// LABEL_top1name
// LABEL_top2name
// LABEL_top3name
// LABEL_top1score
// LABEL_top2score
// LABEL_top3score