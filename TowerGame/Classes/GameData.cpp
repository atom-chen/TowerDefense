#include "GameData.h"
#include "cocos2d.h"
using namespace cocos2d;
GAMEDATA* GAMEDATA::_instance = 0;
GAMEDATA::GAMEDATA(){
	this->init();
}
GAMEDATA* GAMEDATA::getInstance(){
	if(_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::init(){

	//TODO
}