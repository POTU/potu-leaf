#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartUpScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(StartUpScene);
	virtual void update(float delta);

private:
	bool isFirstUpdate;
	bool hasLoaded;
};

#endif
