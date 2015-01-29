#include "LevelSelectLayer.h"
#include "cocos2d.h"
#include "StartScene.h"
#include "GameScene.h"
#include "GameData.h"

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


	Vector<MenuItem*> menuItemVector;
	for(int i=0; i<2; i++){
		std::string strName ="level_"+cocos2d::String::createWithFormat("%d",(i+1))->_string+".png";
		auto level = MenuItemImage::create(strName,strName,CC_CALLBACK_1(LevelSelectLayer::startGame,this));
		  level->setTag(i);
          menuItemVector.pushBack(level);
	}
	auto levelMenu = Menu::createWithArray(menuItemVector);
	levelMenu->alignItemsHorizontallyWithPadding (100);
	levelMenu->setPosition(visibleSize.width/2,visibleSize.height/2);
	
	this->addChild(levelMenu); 


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

void LevelSelectLayer::startGame(Ref* pSender){ 
	//add level logic
    auto button = (Sprite *)pSender;
	GAMEDATA::getInstance()->setCurrentLevel(button->getTag());
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}