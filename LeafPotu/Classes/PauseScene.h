#ifndef PAUSE_SCENE_H
#define PAUSE_SCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class PauseScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene();
	CREATE_FUNC(PauseScene);
private:
	void ExitGame(Ref *pSender, ui::TouchEventType type);
	void CallResetGame(Ref *pSender, ui::TouchEventType type);
	void CallPauseGame(Ref *pSender, ui::TouchEventType type);
};


#endif