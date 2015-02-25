#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	currentWave=0;
}

GAMEDATA* GAMEDATA::getInstance(){
	if(_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState",state);
}

bool GAMEDATA::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState",true);
}

void GAMEDATA::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState",state);
}

bool GAMEDATA::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState",true);
}

float GAMEDATA::getTowerFrequency(){
	return UserDefault::getInstance()->getFloatForKey("towerFrequency",0.8); 
}

int GAMEDATA::getTowerRange(){
	return UserDefault::getInstance()->getIntegerForKey("towerRange",50); 
}

void GAMEDATA::doubleTowerFrequency(){
	auto fre = getTowerFrequency()/2;
	UserDefault::getInstance()->setFloatForKey("towerFrequency",fre);
}

void GAMEDATA::doubleTowerRange(){
	auto range = getTowerRange()*2;
	UserDefault::getInstance()->setFloatForKey("towerFrequency",range);
}
void GAMEDATA::clear(){}