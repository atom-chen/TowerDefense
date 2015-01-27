#include "TopMenu.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Chinese.h"


TopMenu* TopMenu::create(GameLayer* layer){
	TopMenu* ret = new TopMenu();
	if(ret && ret->init(layer)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool TopMenu::init(GameLayer* layer){
	if(!Node::init()){
		return false;
	}
	LoadTopMenu();
	return true;
}
void TopMenu::LoadTopMenu(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add lifeValue label
	lifeValue = Label::create(
		ChineseWord("lifevalue") + cocos2d::String::createWithFormat("%d",10)->_string,
		"Verdana-Bold",24
		);
	lifeValue->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(lifeValue);

	//add wave value
	waveValue = Label::create(
		ChineseWord("lifevalue") + cocos2d::String::createWithFormat("%d",1)->_string+"/"+cocos2d::String::createWithFormat("%d",10)->_string,
		"Verdana-Bold",24
		);
	waveValue->setPosition(visibleSize.width/2,visibleSize.height/2+50);
	this->addChild(waveValue);

}