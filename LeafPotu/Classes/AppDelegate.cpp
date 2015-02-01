#include "AppDelegate.h"
#include "StartUpScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // Initialize Director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Leaf View");
        director->setOpenGLView(glview);
		#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			glview->setFrameSize(1536, 2048);
			glview->setFrameZoomFactor(0.33f);
		#endif
    }

    director->setOpenGLView(glview);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);


	// Resolution Sets
	glview->setDesignResolutionSize(
        designResolutionSize.width,
        designResolutionSize.height,
        ResolutionPolicy::NO_BORDER);
	cocos2d::Size frameSize = glview->getFrameSize();

	if(frameSize.width > mediumResource.size.width)
	{
		FileUtils::getInstance()->addSearchPath(largeResource.directory);
		director->setContentScaleFactor(largeResource.size.width/designResolutionSize.width);
		FileUtils::getInstance()->addSearchPath("HDR/atlas");
        CCLOG("Using HDR");
	}
	else if(frameSize.width > smallResource.size.width)
	{
		FileUtils::getInstance()->addSearchPath(mediumResource.directory);
		director->setContentScaleFactor(mediumResource.size.width/designResolutionSize.width);
		FileUtils::getInstance()->addSearchPath("HD/atlas");
        CCLOG("Using HD");
	}
	else
	{
		FileUtils::getInstance()->addSearchPath(smallResource.directory);
		director->setContentScaleFactor(smallResource.size.width/designResolutionSize.width);
		FileUtils::getInstance()->addSearchPath("SD/atlas");
        CCLOG("Using SD");
	}

	FileUtils::getInstance()->addSearchPath("shaders");
	FileUtils::getInstance()->addSearchPath("spine");
	FileUtils::getInstance()->addSearchPath("UI");
	FileUtils::getInstance()->addSearchPath("audio");

    Scene *scene = StartUpScene::scene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive.
// When comes a phone call,i t's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// This function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

