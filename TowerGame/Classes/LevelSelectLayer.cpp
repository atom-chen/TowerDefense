#include "LevelSelectLayer.h"
#include "cocos2d.h"
#include "StartScene.h"
#include "GameScene.h"

using namespace cocos2d;

bool LevelSelectLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//set background image
	Sprite* background =Sprite::create("level_select_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	auto level = MenuItemImage::create("Level_1.png","Level_1.png",CC_CALLBACK_0(LevelSelectLayer::startGame,this));
	Menu* level_1 = Menu::create(level, NULL);
	level_1->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(level_1); 


	//add goback button
	auto goBackBtn = MenuItemImage::create("ui_stage_intro_back.png","ui_stage_intro_back_pressed.png",CC_CALLBACK_0(LevelSelectLayer::goBack,this));
	Menu* bakcMenu = Menu::create(goBackBtn, NULL);
	bakcMenu->setPosition(visibleSize.width/2-200,visibleSize.height/2-200);
	this->addChild(bakcMenu); 

	return true;
}

void LevelSelectLayer::goBack(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,StartScene::createScene()));
}

void LevelSelectLayer::startGame(){ 
	//add level logic
   Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}