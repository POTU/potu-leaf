#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Helpers.h"

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

	Size screen = Director::getInstance()->getWinSize();

	//BG
	Sprite* bg = Sprite::createWithSpriteFrameName("MENU_tausta.png");
	bg->setPosition(screen.width/2, screen.height/2);
	this->addChild(bg);

	Sprite* logo = Sprite::createWithSpriteFrameName("Logo.png");
	logo->setPosition(screen.width/2, screen.height-330);
	logo->setScale(0.5f);
	this->addChild(logo);


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

	//ui::Text* labelTop1Name = (ui::Text*)uiNode->getChildByName("LABEL_top1name");
	//labelTop1Name->setText(CCUserDefault::getInstance()->getStringForKey("Top1Name"));
	
	//ui::Text* labelTop2Name = (ui::Text*)uiNode->getChildByName("LABEL_top2name");
	//labelTop2Name->setText(CCUserDefault::getInstance()->getStringForKey("Top2Name"));

	//ui::Text* labelTop3Name = (ui::Text*)uiNode->getChildByName("LABEL_top3name");
	//labelTop3Name->setText(CCUserDefault::getInstance()->getStringForKey("Top3Name"));

	ui::Text* labelTop1Score = (ui::Text*)uiNode->getChildByName("LABEL_top1score");
	labelTop1Score->setText(rd::StringFromInt(CCUserDefault::getInstance()->getIntegerForKey("Top1Score")));

	ui::Text* labelTop2Score = (ui::Text*)uiNode->getChildByName("LABEL_top2score");
	labelTop1Score->setText(rd::StringFromInt(CCUserDefault::getInstance()->getIntegerForKey("Top2Score")));

	ui::Text* labelTop3Score = (ui::Text*)uiNode->getChildByName("LABEL_top3score");
	labelTop1Score->setText(rd::StringFromInt(CCUserDefault::getInstance()->getIntegerForKey("Top3Score")));

	return true;
}

void MenuScene::PlayGame(Ref *pSender, ui::TouchEventType type)
{
	TransitionFade* gameScene;
	switch (type)
	{
		case ui::TouchEventType::TOUCH_EVENT_BEGAN:
			break;
		case ui::TouchEventType::TOUCH_EVENT_MOVED:
			// TODO
			break;
		case ui::TouchEventType::TOUCH_EVENT_ENDED:
            SimpleAudioEngine::getInstance()->playEffect("button.mp3");

			gameScene = TransitionFade::create(1.0f, GameScene::scene());
			Director::getInstance()->replaceScene(gameScene);
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