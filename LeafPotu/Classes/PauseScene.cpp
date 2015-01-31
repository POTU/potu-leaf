#include "PauseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "GameManager.h"

#include <SimpleAudioEngine.h>


using namespace cocos2d;
using namespace cocos2d::ui;

Scene* PauseScene::scene()
{
	Scene *scene = Scene::create();
	PauseScene *layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Node* uiNode = CSLoader::createNode("PauseScene.csb");
	this->addChild(uiNode);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto windowSize = Director::getInstance()->getWinSize();

	ui::Button* exitButton = (ui::Button*)uiNode->getChildByName("BTN_exit");
	exitButton->addTouchEventListener(this, toucheventselector(PauseScene::ExitGame));
	exitButton->setPosition(Vec2(exitButton->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));

	ui::Button* resetButton = (ui::Button*)uiNode->getChildByName("BTN_reset");
	resetButton->addTouchEventListener(this, toucheventselector(PauseScene::CallResetGame));
	resetButton->setPosition(Vec2(resetButton->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));

	ui::Button* resumeButton = (ui::Button*)uiNode->getChildByName("BTN_resume");
	resumeButton->addTouchEventListener(this, toucheventselector(PauseScene::CallPauseGame));
	resumeButton->setPosition(Vec2(resumeButton->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));
	return true;
}

void PauseScene::CallResetGame(Ref *pSender, ui::TouchEventType type)
{
	GameManager gameManager;
	switch (type)
	{
	case ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case ui::TouchEventType::TOUCH_EVENT_MOVED:
		// TODO
		break;
	case ui::TouchEventType::TOUCH_EVENT_ENDED:
		gameManager.ResetGame();
		break;
	case ui::TouchEventType::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}

}


void PauseScene::CallPauseGame(Ref *pSender, ui::TouchEventType type)
{
	GameManager gameManager;
	switch (type)
	{
	case ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case ui::TouchEventType::TOUCH_EVENT_MOVED:
		// TODO
		break;
	case ui::TouchEventType::TOUCH_EVENT_ENDED:
		gameManager.PauseGame();
		break;
	case ui::TouchEventType::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}

}

void PauseScene::ExitGame(Ref *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case ui::TouchEventType::TOUCH_EVENT_MOVED:
		// TODO
		break;
	case ui::TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(MenuScene::scene());
		break;
	case ui::TouchEventType::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}

}
