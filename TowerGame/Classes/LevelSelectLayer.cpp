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

	/*auto startGameBtn = MenuItemImage::create("start_game.png","start_game.png",CC_CALLBACK_0(LevelSelectLayer::startGame,this));
	Menu* menu = Menu::create(startGameBtn, NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2-150);
	this->addChild(menu); */


	Vector<MenuItem*> menuItemVector;
	for(int i=0; i<2; i++){
		std::string strNoraml ="level_normal_"+cocos2d::String::createWithFormat("%d",(i+1))->_string+".png";
		std::string strSelect ="level_select_"+cocos2d::String::createWithFormat("%d",(i+1))->_string+".png";
		auto level = MenuItemImage::create(strNoraml,strSelect,CC_CALLBACK_1(LevelSelectLayer::levelSelect,this));
		level->setTag(i);
		menuItemVector.pushBack(level);
	}
	auto levelMenu = Menu::createWithArray(menuItemVector);
	levelMenu->alignItemsHorizontallyWithPadding (100);
	levelMenu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(levelMenu); 
	return true;
}


void LevelSelectLayer::levelSelect(Ref* pSender){ 
	//add level logic
    auto button = (Sprite *)pSender;
	GAMEDATA::getInstance()->setCurrentLevel(button->getTag());
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
	
}

//void LevelSelectLayer::startGame(){
//	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
//}