#include "GameOverLayer.h"
#include "GameScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"



using namespace cocos2d;

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//set background image
	Sprite* background =Sprite::create("background.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	//add goback button
	auto startGameBtn = MenuItemImage::create("ui_start_normal.png","ui_start_pressed.png",CC_CALLBACK_0(GameOverLayer::goBack,this));
	Menu* menu = Menu::create(startGameBtn, NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu); 

	return true;
}


void GameOverLayer::goBack(){
		Director::getInstance()->replaceScene(TransitionFade::create(1,StartScene::createScene()));
	
}