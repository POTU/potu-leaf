#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto windowSize = Director::getInstance()->getWinSize();


	ui::Button* playButton = (ui::Button*)uiNode->getChildByName("BTN_play");
	playButton->addTouchEventListener(this, toucheventselector(MenuScene::PlayGame));

	ui::Button* muteButton = (ui::Button*)uiNode->getChildByName("BTN_mute");
	muteButton->addTouchEventListener(this, toucheventselector(MenuScene::MuteGame));
	muteButton->setPosition(Vec2(muteButton->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));

	ui::Button* exitButton = (ui::Button*)uiNode->getChildByName("BTN_exit");
	exitButton->addTouchEventListener(this, toucheventselector(MenuScene::ExitGame));
	exitButton->setPosition(Vec2(exitButton->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));

	ui::Text* labelTop1Name = (ui::Text*)uiNode->getChildByName("LABEL_top1name");
	labelTop1Name->setText("ASD");

	ui::Text* labelTop2Name = (ui::Text*)uiNode->getChildByName("LABEL_top2name");
	labelTop2Name->setText("DAS");

	ui::Text* labelTop3Name = (ui::Text*)uiNode->getChildByName("LABEL_top3name");
	labelTop3Name->setText("SDA");

	ui::Text* labelTop1Score = (ui::Text*)uiNode->getChildByName("LABEL_top1score");
	labelTop1Score->setText("321");

	ui::Text* labelTop2Score = (ui::Text*)uiNode->getChildByName("LABEL_top2score");
	labelTop2Score->setText("231");

	ui::Text* labelTop3Score = (ui::Text*)uiNode->getChildByName("LABEL_top3score");
	labelTop3Score->setText("123");

	return true;
}

void MenuScene::PlayGame(Ref *pSender, ui::TouchEventType type)
{
	switch (type)
	{
		case ui::TouchEventType::TOUCH_EVENT_BEGAN:
			break;
		case ui::TouchEventType::TOUCH_EVENT_MOVED:
			// TODO
			break;
		case ui::TouchEventType::TOUCH_EVENT_ENDED:
            SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			Director::getInstance()->replaceScene(GameScene::scene());
			break;
		case ui::TouchEventType::TOUCH_EVENT_CANCELED:
			// TODO
			break;
		default:
			// TODO
			break;
	}
}

void MenuScene::MuteGame(Ref *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case ui::TouchEventType::TOUCH_EVENT_MOVED:
		// TODO
		break;
	case ui::TouchEventType::TOUCH_EVENT_ENDED:
	{
		if (muted == true)
		{
			muted = false;
            SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
			SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
		}
		else
		{
			muted = true;
            SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0);
			SimpleAudioEngine::getInstance()->setEffectsVolume(0.0);
		}
	}

		break;
	case ui::TouchEventType::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}
}

void MenuScene::ExitGame(Ref *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case ui::TouchEventType::TOUCH_EVENT_MOVED:
		// TODO
		break;
	case ui::TouchEventType::TOUCH_EVENT_ENDED:
        SimpleAudioEngine::getInstance()->playEffect("button.mp3");
		exit(0);
		break;
	case ui::TouchEventType::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}

}