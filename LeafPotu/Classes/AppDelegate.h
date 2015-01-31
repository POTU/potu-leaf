#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

enum
{
	kResourceSetSD = 1,
	kResourceSetHD,
	kResourceSetHDR,
};

typedef struct tagResource
{
	cocos2d::Size size;
	char directory[100];
} Resource;

static Resource smallResource = { cocos2d::Size(1536/4,2272/4), "SD" };
static Resource mediumResource = { cocos2d::Size(1536/2,2272/2), "HD" };
static Resource largeResource = { cocos2d::Size(1536,2272), "HDR" };
static cocos2d::Size designResolutionSize = cocos2d::Size(1536,2272);


class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
	virtual void initGLContextAttrs();
    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

