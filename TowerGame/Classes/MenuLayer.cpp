#include "MenuLayer.h"
#include "LevelSelectScene.h"
#include "BlinkTitle.h"

bool MenuLayer::init(){

	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//set background image
	Sprite* background =Sprite::create("background.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	//add start button

	BlinkTitle* title = BlinkTitle::create("start_game.png");;
	title->setPosition(visibleSize.width/2, 100);
	this->addChild(title); 

	auto startGameBtn = MenuItemImage::create("start_game.png","start_game.png",CC_CALLBACK_0(MenuLayer::startGame,this));
	Menu* menu = Menu::create(startGameBtn, NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu); 

	return true;
}

void MenuLayer::startGame(){
	CCLOG("click click click");
    Director::getInstance()->replaceScene(TransitionFade::create(1,LevelSelectScene::create()));
}