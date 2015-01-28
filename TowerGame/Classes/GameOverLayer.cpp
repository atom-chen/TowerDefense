#include "GameOverLayer.h"
#include "LevelSelectScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"



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
	auto startGameBtn = MenuItemImage::create("ui_stage_intro_back.png","ui_stage_intro_back_pressed.png",CC_CALLBACK_0(GameOverLayer::goBack,this));
	Menu* menu = Menu::create(startGameBtn, NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu); 

	return true;
}


void GameOverLayer::goBack(){
		Director::getInstance()->replaceScene(TransitionFade::create(1,LevelSelectScene::create()));
	
}