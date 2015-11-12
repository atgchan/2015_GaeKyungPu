#include "pch.h"
#include "MainScene.h"
#include "AppDelegate.h"
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

//이게 본문이다!
bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		//glview = GLViewImpl::createWithFullScreen("practice");
		glview = GLViewImpl::createWithRect("TESTuDO", Rect(0, 0, 1280, 800));//창모드
        director->setOpenGLView(glview);
    }

    // FPS on/off
    director->setDisplayStats(true);
    // FPS 셋팅
    director->setAnimationInterval(1.0 / 60);

    // 첫 scene 실행
	auto mainScene = MainScene::createScene();
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
