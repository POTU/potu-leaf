#ifndef MENU_SCENE_H
#define MENU_SCENE_H


#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene();
	CREATE_FUNC(MenuScene);
private:
	void PlayGame(Ref *pSender, ui::TouchEventType type);
	void MuteGame(Ref *pSender, ui::TouchEventType type);
	void ExitGame(Ref *pSender, ui::TouchEventType type);
	bool muted;
};


#endif