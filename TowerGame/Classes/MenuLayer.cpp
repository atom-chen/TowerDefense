#include "MenuLayer.h"

bool MenuLayer::init(){

	if(!Layer::init()){
		return false;
	}
	auto startGameBtn = MenuItemImage::create("ui_start_normal.png","ui_start_pressed.png",CC_CALLBACK_0(MenuLayer::startGame,this));
	startGameBtn->setPosition(240,400);
	this->addChild(startGameBtn);
	auto scaleSmall = ScaleTo::create(0.8,0.7);
	auto scaleBig = ScaleTo::create(0.8,1);
	auto delay = DelayTime::create(0);
	auto seq = Sequence::create(scaleSmall,delay,scaleBig,delay->clone(),NULL);
	startGameBtn->runAction(RepeatForever::create(seq));
    
	return true;
}

void MenuLayer::startGame(){
    //Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}