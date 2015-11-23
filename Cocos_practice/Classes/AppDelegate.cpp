#include "pch.h"
#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0; //flag for packages manager
}

//�̰� �����̴�!
bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		//glview = GLViewImpl::createWithFullScreen("practice");
		glview = GLViewImpl::createWithRect("TESTuDO", Rect(0, 0, 1280, 800));//â���
        director->setOpenGLView(glview);
    }

    // FPS on/off
    director->setDisplayStats(true);
    // FPS ����
    director->setAnimationInterval(1.0f / 60);

	//resourcefile load!
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/ui_image.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Character/unit_blue.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Character/unit_red.plist");

    // ù scene ����
	auto mainScene = MainScene::CreateScene();
	director->runWithScene(mainScene);
	
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
