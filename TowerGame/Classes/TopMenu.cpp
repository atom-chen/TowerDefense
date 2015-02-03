#include "TopMenu.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Chinese.h"
#include "GameData.h"
#include "TopMenu.h"
#include "GameLayer.h"
#include "GameState.h"


TopMenu* TopMenu::getInstance(){
	TopMenu* ret = new TopMenu();
	if(ret && ret->init()){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool TopMenu::init(){
	if(!Node::init()){
		return false;
	}
	scheduleUpdate();
	LoadTopMenu();	
	return true;
}

void TopMenu::LoadTopMenu(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	GAMEDATA *data = GAMEDATA::getInstance();
	//add lifeValue label
	lifeValue = Label::create(
		ChineseWord("lifevalue") + cocos2d::String::createWithFormat(":%d",data->getLifeValue())->_string,
		"Verdana-Bold",24
		);
	lifeValue->setPosition(50,visibleSize.height/2-200);
	this->addChild(lifeValue);

	//add wave value
	waveValue = Label::create(
		ChineseWord("waves") + cocos2d::String::createWithFormat(":%d",data->getCurrentWave()+1)->_string+"/"+cocos2d::String::createWithFormat("%d",data->waves.size())->_string,
		"Verdana-Bold",24
		);
	waveValue->setPosition(150,visibleSize.height/2-200);
	this->addChild(waveValue);

	//add player god value
	playerGold = Label::create(ChineseWord("gold")+cocos2d::String::createWithFormat(":%d",data->getPlayerGold())->_string,
		"Verdana-Bold",24
		);
	playerGold->setPosition(250,visibleSize.height/2-200);
	this->addChild(playerGold);
}
void TopMenu::refresh(){
	GAMEDATA *data = GAMEDATA::getInstance();
	lifeValue->setString(ChineseWord("lifevalue") + cocos2d::String::createWithFormat(":%d",data->getLifeValue())->_string);
	waveValue->setString(ChineseWord("waves") + cocos2d::String::createWithFormat(":%d",data->getCurrentWave()+1)->_string+"/"+cocos2d::String::createWithFormat("%d",data->waves.size())->_string);
	playerGold->setString(ChineseWord("gold")+cocos2d::String::createWithFormat(":%d",data->getPlayerGold())->_string);
}

void TopMenu::update(float dt){
	if(GAMESTATE::getInstance()->getRefreshTopmenu()){
		refresh();
		GAMESTATE::getInstance()->setRefreshTopmenu(false);
	}
}