#include "GameOverLayer.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"

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
	this->addChild(background);


	return true;
}
