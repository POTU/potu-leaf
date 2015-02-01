#include "EndScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Helpers.h"
#include "SimpleAudioEngine.h"
#include "GlobalManager.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

Scene* EndScene::scene()
{
	Scene *scene = Scene::create();
	EndScene *layer = EndScene::create();
	scene->addChild(layer);
	return scene;
}

bool EndScene::init()
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
	

	PlayerScore = GlobalManager::getInstance()->PlayerScore;

	Node* uiNode = CSLoader::createNode("EndScene.csb");
	this->addChild(uiNode);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto windowSize = Director::getInstance()->getWinSize();

	ui::Button* exitButton = (ui::Button*)uiNode->getChildByName("BTN_exit");
	exitButton->addTouchEventListener(this, toucheventselector(EndScene::ExitGame));

	ui::Button* resetButton = (ui::Button*)uiNode->getChildByName("BTN_play");
	resetButton->addTouchEventListener(this, toucheventselector(EndScene::CallResetGame));


	ui::Text* labelScore = (ui::Text*)uiNode->getChildByName("LABEL_score");
	labelScore->setText(rd::StringFromInt(GlobalManager::getInstance()->PlayerScore));

	//ui::TextField* inputTag = (ui::TextField*)uiNode->getChildByName("INPUT_tag");

	int Position = 0;

	if (PlayerScore > CCUserDefault::getInstance()->getIntegerForKey("Top3Score"))
	{
		Position = 3;
		if (PlayerScore > CCUserDefault::getInstance()->getIntegerForKey("Top2Score"))
		{
			Position = 2;
			if (PlayerScore > CCUserDefault::getInstance()->getIntegerForKey("Top1Score"))
			{
				Position = 1;
			}
		}
	}

	switch (Position)
	{
		case 1:
			//CCUserDefault::getInstance()->setStringForKey("Top3Name", CCUserDefault::getInstance()->getStringForKey("Top2Name"));
			CCUserDefault::getInstance()->setIntegerForKey("Top3Score", CCUserDefault::getInstance()->getIntegerForKey("Top2Score"));

			//CCUserDefault::getInstance()->setStringForKey("Top2Name", CCUserDefault::getInstance()->getStringForKey("Top1Name"));
			CCUserDefault::getInstance()->setIntegerForKey("Top2Score", CCUserDefault::getInstance()->getIntegerForKey("Top1Score"));

			//CCUserDefault::getInstance()->setStringForKey("Top1Name", PlayerName);
			CCUserDefault::getInstance()->setIntegerForKey("Top1Score", PlayerScore);
			break;
		case 2:
			//CCUserDefault::getInstance()->setStringForKey("Top3Name", CCUserDefault::getInstance()->getStringForKey("Top2Name"));
			CCUserDefault::getInstance()->setIntegerForKey("Top3Score", CCUserDefault::getInstance()->getIntegerForKey("Top2Score"));

			//CCUserDefault::getInstance()->setStringForKey("Top2Name", PlayerName);
			CCUserDefault::getInstance()->setIntegerForKey("Top2Score", PlayerScore);
			break;
		case 3:
			//CCUserDefault::getInstance()->setStringForKey("Top3Name", PlayerName);
			CCUserDefault::getInstance()->setIntegerForKey("Top3Score", PlayerScore);
			break;

		case 0:
			break;
	}


	return true;
}

void EndScene::CallResetGame(Ref *pSender, ui::TouchEventType type)
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
		SimpleAudioEngine::getInstance()->playEffect("Audio/button.mp3");
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

void EndScene::ExitGame(Ref *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case ui::TouchEventType::TOUCH_EVENT_MOVED:
		// TODO
		break;
	case ui::TouchEventType::TOUCH_EVENT_ENDED:
		SimpleAudioEngine::getInstance()->playEffect("Audio/button.mp3");
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
