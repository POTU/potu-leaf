#ifndef GAME_SCENE_H
#define GAME_SCENE_H


#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "TileableWorld.h"
#include "GameManager.h"

#ifdef DEBUG_PHYSICS
#include "GLES-Render.h"
#endif

class GameScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
	virtual void onExit();
	virtual void update(float delta);


	virtual bool potuTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void potuTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void potuTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void potuTouchCanceled(cocos2d::Touch* touch, cocos2d::Event* event);


#ifdef DEBUG_PHYSICS
	virtual void custdraw();
#endif
protected:
#ifdef DEBUG_PHYSICS
    cocos2d::kmMat4 _modelViewMV;
    void onDraw();
    cocos2d::CustomCommand _customCommand;
#endif

private:
#ifdef DEBUG_PHYSICS
	GLESDebugDraw* debugDraw;
#endif

	cocos2d::EventListenerTouchOneByOne* listener;

	b2World* mWorld;
	cocos2d::Layer* mBgLayer;
	cocos2d::Layer* mGameLayer;
	cocos2d::Layer* mUILayer;

	GameManager* mGameManager;

	TileableWorld* tw;
};


#endif