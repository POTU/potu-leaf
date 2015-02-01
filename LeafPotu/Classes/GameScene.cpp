#include "GameScene.h"
#include "GameManager.h"
#include "StartUpScene.h"
#include "TileableWorld.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "spine/spine-cocos2dx.h"
#include "Helpers.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

Scene* GameScene::scene()
{
    Scene *scene = Scene::createWithPhysics();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

	cocos2d::Size screen = Director::getInstance()->getWinSize();

	listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::potuTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::potuTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::potuTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	shouldPause = false;

	mBgLayer = Layer::create();
	this->addChild(mBgLayer);

	mGameLayer = Layer::create();
	this->addChild(mGameLayer);

	mOverLayer = Layer::create();
	this->addChild(mOverLayer);

	mUILayer = Layer::create();
	this->addChild(mUILayer);

	auto gravityVec = b2Vec2(0, 0);
	mWorld = new b2World(gravityVec);
    
	mTileableWorld = NULL;
    mTileableWorld = new TileableWorld();
	mTileableWorld->init(mOverLayer, mWorld, mBgLayer);
	
    mGameManager = GameManager::getInstance();
	mGameManager->init(mGameLayer, mTileableWorld, mWorld);

	Node* uiNode = CSLoader::createNode("InGameScene.csb");
	this->addChild(uiNode);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto windowSize = Director::getInstance()->getWinSize();


	ui::Button* pauseButton = (ui::Button*)uiNode->getChildByName("BTN_pause");
	pauseButton->addTouchEventListener(this, toucheventselector(GameScene::CallPause));
	pauseButton->setPosition(Vec2(pauseButton->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));

	ui::Button* muteButton = (ui::Button*)uiNode->getChildByName("BTN_mute");
	muteButton->addTouchEventListener(this, toucheventselector(GameScene::CallMute));
	muteButton->setPosition(Vec2(muteButton->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));

	Score = 0;
	ScoreFloat = 0;
	labelScore = (ui::Text*)uiNode->getChildByName("LABEL_score");
	labelScore->setPosition(Vec2(labelScore->getPosition().x, visibleSize.height - ((windowSize.height - visibleSize.height) / 2)));
	labelScore->setText(rd::StringFromInt(Score));

#ifdef DEBUG_PHYSICS
	debugDraw = new GLESDebugDraw(PTM_RATIO);
	mWorld->SetDebugDraw(debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);
#endif

	//BG
	mWaterBg = Sprite::createWithSpriteFrameName("water.png");
	mWaterBg->setScale(4.0f);
	mWaterBg->setPosition(screen.width/2, screen.height/2);
	mBgLayer->addChild(mWaterBg, -1);

	this->scheduleUpdate();

    return true;
}

void GameScene::onExit()
{
	if (shouldPause == true)
	{
		shouldPause = false;
	}
	else
	{
		if (mGameManager) delete mGameManager;
		if (mTileableWorld) delete mTileableWorld;
		delete mWorld;
	}
	Layer::onExit();
}

void GameScene::update(float delta)
{
	mTileableWorld->update(delta);
	mGameManager->update(delta);

	static double UPDATE_INTERVAL = 1.0f/60.0f;
	static double MAX_CYCLES_PER_FRAME = 5;
	static double timeAccumulator = 0;
 
	timeAccumulator += delta;    
	if (timeAccumulator > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
		timeAccumulator = UPDATE_INTERVAL;
	}
	int32 velocityIterations = 6;
	int32 positionIterations = 6;
	while (timeAccumulator >= UPDATE_INTERVAL) {        
		timeAccumulator -= UPDATE_INTERVAL;        
		mWorld->Step(UPDATE_INTERVAL, velocityIterations, positionIterations);
		mWorld->ClearForces();
	}

	ScoreFloat += delta * 6.0f;
	if (ScoreFloat >= 1)
	{
		ScoreFloat = 0;
		Score++;
		labelScore->setText(rd::StringFromInt(Score));
	}

#ifdef DEBUG_PHYSICS
	this->custdraw();
#endif
	if (shouldPause == true)
	{
		mGameManager->PauseGame(true);
	}
}


void GameScene::potuTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

bool GameScene::potuTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void GameScene::potuTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    mGameManager->InputCoordinates(touch->getLocation());

	// Create ripple
	cocos2d::Node* rippleNode = Node::create();
	rippleNode->setPosition(touch->getLocation());
	mBgLayer->addChild(rippleNode);

	Sequence* nodeSeq = Sequence::createWithTwoActions(MoveBy::create(2.0f, cocos2d::Vec2(0,-600)), CallFuncN::create(CC_CALLBACK_1(GameScene::rippleDeleteCallback, this)));
	rippleNode->runAction(nodeSeq);

	spine::SkeletonAnimation* rippleAnimation = spine::SkeletonAnimation::createWithFile("skeleton.json", rd::atlasName("skeleton"));
	rippleNode->addChild(rippleAnimation);
	rippleAnimation->setAnimation(0, "animation", false);

	rippleNode->setRotation(rd::RandFloat(-180, 180));
}

void GameScene::potuTouchCanceled(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void GameScene::CallPause(Ref *pSender, ui::TouchEventType type)
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
		shouldPause = true;
		break;
	case ui::TouchEventType::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}
}

void GameScene::CallMute(Ref *pSender, ui::TouchEventType type)
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
		mGameManager->MuteGame();
		break;
	case ui::TouchEventType::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}
}


#ifdef DEBUG_PHYSICS
void GameScene::custdraw()
{
	GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
	kmGLPushMatrix();
	kmGLGetMatrix(KM_GL_MODELVIEW, &_modelViewMV);
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(GameScene::onDraw, this);
	Director::getInstance()->getRenderer()->addCommand(&_customCommand);
	kmGLPopMatrix();  
}
void GameScene::onDraw()
{
    kmMat4 oldMV;
    kmGLGetMatrix(KM_GL_MODELVIEW, &oldMV);
    kmGLLoadMatrix(&_modelViewMV);
    mWorld->DrawDebugData();
    kmGLLoadMatrix(&oldMV);
}
#endif


void GameScene::rippleDeleteCallback(cocos2d::Node* pSender)
{
	pSender->removeFromParentAndCleanup(true);
}
