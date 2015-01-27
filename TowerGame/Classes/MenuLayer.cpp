#include "MenuLayer.h"
#include "LevelSelectScene.h"

bool MenuLayer::init(){

	if(!Layer::init()){
		return false;
	}
	//add start button
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto startGameBtn = MenuItemImage::create("ui_start_normal.png","ui_start_pressed.png",CC_CALLBACK_0(MenuLayer::startGame,this));
	Menu* menu = Menu::create(startGameBtn, NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu); 

	return true;
}

void MenuLayer::startGame(){
    Director::getInstance()->replaceScene(TransitionFade::create(1,LevelSelectScene::create()));
}