#include "GameOverLayer.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameData.h"
#include "GameState.h"
#include "StartScene.h"



using namespace cocos2d;

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//set background image
	Sprite* background =Sprite::create("background.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	//add goback button
	auto goback = MenuItemImage::create("go_back.png","go_back.png",CC_CALLBACK_0(GameOverLayer::goBack,this));
	auto next = MenuItemImage::create("next_level.png","next_level.png",CC_CALLBACK_0(GameOverLayer::nextLevel,this));
	auto retry = MenuItemImage::create("retry.png","retry.png",CC_CALLBACK_0(GameOverLayer::retry,this));
	if(!GAMESTATE::getInstance()->getLevelResult()){
		next->setVisible(false);
	}
	Menu* menu = Menu::create(goback,retry,next,NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu); 

	return true;
}

//goto levle select scene
void GameOverLayer::goBack(){
		Director::getInstance()->replaceScene(TransitionFade::create(1,StartScene::createScene()));	
}

//goto next level
void GameOverLayer::nextLevel(){
	GAMEDATA::getInstance()->setCurrentLevel(GAMEDATA::getInstance()->getCurrentLevel()+1);
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

//try this current again
void GameOverLayer::retry(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}