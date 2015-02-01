#ifndef END_SCENE_H
#define END_SCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class EndScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene();
	CREATE_FUNC(EndScene);
private:
	int PlayerScore;
	std::string PlayerName;
	void ExitGame(Ref *pSender, ui::TouchEventType type);
	void CallResetGame(Ref *pSender, ui::TouchEventType type);
	void leaderboardName(Ref *pSender, ui::TextField::EventType type);
};


#endif