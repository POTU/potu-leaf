#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui\CocosGUI.h"

#include "GameScene.h"
#include <SimpleAudioEngine.h>

using namespace cocos2d;
using namespace cocos2d::ui;

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

	Node* uiNode = CSLoader::createNode("MenuScene.csb");
	this->addChild(uiNode);

	ui::Button* playButton = (ui::Button*)uiNode->getChildByName("BTN_play");
	playButton->addTouchEventListener(this, toucheventselector(MenuScene::PlayGame));
	uiNode->addChild(playButton);

	ui::Button* muteButton = (ui::Button*)uiNode->getChildByName("BTN_mute");
	muteButton->addTouchEventListener(this, toucheventselector(MenuScene::MuteGame));
	uiNode->addChild(muteButton);

	ui::Button* exitButton = (ui::Button*)uiNode->getChildByName("BTN_exit");
	exitButton->addTouchEventListener(this, toucheventselector(MenuScene::ExitGame));
	uiNode->addChild(exitButton);

	ui::Text* labelTop1Name = (ui::Text*)uiNode->getChildByName("LABEL_top1name");
	labelTop1Name->setText("Hello Cocos!");
	labelTop1Name->setFontName("Marker Felt");
	labelTop1Name->setFontSize(30);
	labelTop1Name->setColor(Color3B(159, 168, 176));
	uiNode->addChild(labelTop1Name);

	ui::Text* labelTop2Name = (ui::Text*)uiNode->getChildByName("LABEL_top2name");
	labelTop2Name->setText("Hello Cocos!");
	labelTop2Name->setFontName("Marker Felt");
	labelTop2Name->setFontSize(30);
	labelTop2Name->setColor(Color3B(159, 168, 176));
	uiNode->addChild(labelTop2Name);

	ui::Text* labelTop3Name = (ui::Text*)uiNode->getChildByName("LABEL_top3name");
	labelTop3Name->setText("Hello Cocos!");
	labelTop3Name->setFontName("Marker Felt");
	labelTop3Name->setFontSize(30);
	labelTop3Name->setColor(Color3B(159, 168, 176));
	uiNode->addChild(labelTop3Name);

	ui::Text* labelTop1Score = (ui::Text*)uiNode->getChildByName("LABEL_top1score");
	labelTop1Score->setText("Hello Cocos!");
	labelTop1Score->setFontName("Marker Felt");
	labelTop1Score->setFontSize(30);
	labelTop1Score->setColor(Color3B(159, 168, 176));
	uiNode->addChild(labelTop1Score);

	ui::Text* labelTop2Score = (ui::Text*)uiNode->getChildByName("LABEL_top2score");
	labelTop2Score->setText("Hello Cocos!");
	labelTop2Score->setFontName("Marker Felt");
	labelTop2Score->setFontSize(30);
	labelTop2Score->setColor(Color3B(159, 168, 176));
	uiNode->addChild(labelTop2Score);

	ui::Text* labelTop3Score = (ui::Text*)uiNode->getChildByName("LABEL_top3score");
	labelTop3Score->setText("Hello Cocos!");
	labelTop3Score->setFontName("Marker Felt");
	labelTop3Score->setFontSize(30);
	labelTop3Score->setColor(Color3B(159, 168, 176));
	uiNode->addChild(labelTop3Score);

	return true;
}

void MenuScene::PlayGame(Ref *pSender, ui::TouchEventType type)
{
	Director::getInstance()->runWithScene(GameScene::scene());
}

void MenuScene::MuteGame(Ref *pSender, ui::TouchEventType type)
{
	if (muted == true)
	{
		muted = false;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
	}
	else
	{
		muted = true;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
	}
}

void MenuScene::ExitGame(Ref *pSender, ui::TouchEventType type)
{
	
}