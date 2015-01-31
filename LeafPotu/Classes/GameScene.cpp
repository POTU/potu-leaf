#include "StartUpScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::scene()
{
    Scene *scene = Scene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	this->scheduleUpdate();

	mBgLayer = Layer::create();
	this->addChild(mBgLayer);

	mGameLayer = Layer::create();
	this->addChild(mGameLayer);

	mUILayer = Layer::create();
	this->addChild(mUILayer);
    
    auto sprite = Sprite::create("HelloWorld.png");
    cocos2d::Size screen = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(screen.width / 2, screen.height / 2));
    sprite->setScale(2.0f, 2.0f);
    mBgLayer->addChild(sprite);

	// Physics
	b2Vec2 gravityVec = b2Vec2(0,0);
	mWorld = new b2World(gravityVec);

#ifdef DEBUG_PHYSICS
	debugDraw = new GLESDebugDraw( PTM_RATIO );
	mWorld->SetDebugDraw(debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);
#endif

    return true;
}

void GameScene::onExit()
{
	delete mWorld;
	Layer::onExit();
}

void GameScene::update(float delta)
{
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
		mWorld->Step(
            UPDATE_INTERVAL, velocityIterations, positionIterations);
		mWorld->ClearForces();
	}

#ifdef DEBUG_PHYSICS
	this->custdraw();
#endif
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