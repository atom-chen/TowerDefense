#include "AppDelegate.h"
#include "StartScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto eglView = director->getOpenGLView();
	if(!eglView) {
		eglView = GLViewImpl::create("Tower");
		director->setOpenGLView(eglView);
	}

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	eglView->setDesignResolutionSize(800, 480, kResolutionExactFit);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(visibleSize.width/visibleSize.height > 800/480){
		eglView->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);
	}
	else{
		eglView->setDesignResolutionSize(800, 480, ResolutionPolicy::NO_BORDER);
	}
#endif
	// create a scene. it's an autorelease object
	auto scene = StartScene::createScene();


	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
