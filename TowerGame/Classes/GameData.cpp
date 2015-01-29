#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){

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

//return current level life value
void GAMEDATA::initLifeValue(int level){
  static const int Value[10][2] =
	{
		{0, 5},
		{1, 9},
		{2, 8},
		{3, 7},
		{4, 6},
		{5, 5},
		{6, 4},
		{7, 3},
		{8, 2},
		{9, 1},
	};
	if(level>9 || level<0){
		lifeValue= 0;
	}
	lifeValue=Value[level][1];
}

int GAMEDATA::getLifeValue(){
	return lifeValue;
}
void GAMEDATA::setLifeValue(int value){
	lifeValue=value;
}

//return current level life value
void GAMEDATA::initPlayerGold(int level){
	static const int Gold[10][2] =
	{
		{0, 100},
		{1, 200},
		{2, 300},
		{3, 400},
		{4, 500},
		{5, 600},
		{6, 700},
		{7, 800},
		{8, 900},
		{9, 1000},
	};
	if(level>9 || level<0){
		playerGold=0;
	}
	playerGold=Gold[level][1];
}

int GAMEDATA::getPlayerGold(){
	return playerGold;
}

void GAMEDATA::setPlayerGold(int gold){
	playerGold=gold;
}

void GAMEDATA::setCurrentLevel(int lev){
	Level =lev;
}

int GAMEDATA::getCurrentLevel(){
	return Level;
}

void GAMEDATA::initLevelInfo(int Level){
	initPlayerGold(Level);
	initLifeValue(Level);
}

void GAMEDATA::clean(){
	waypoints.clear();
	targets.clear();
	waves.clear();
	towers.clear();
	projectiles.clear();
}

int GAMEDATA::getPriceByImageName(String s){
	if(s.compare("machinegunturret.png")==0){
		return 50;
	}else if(s.compare("tower_damage.png")==0){
		return 80;
	}
} 