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

void GAMEDATA::setMaxLevel(int lev){
	UserDefault::getInstance()->setIntegerForKey("LevelNum",lev);
}

int GAMEDATA::getMaxLevel(){
	return UserDefault::getInstance()->getIntegerForKey("LevelNum",0);
}

void GAMEDATA::setNextLevelFile(std::string filename){
	UserDefault::getInstance()->setStringForKey("LevelNum",filename);
}
std::string GAMEDATA::getNextLevelFile(){
	return UserDefault::getInstance()->getStringForKey("LevelNum");
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
	Level =lev;}

int GAMEDATA::getCurrentLevel(){
	return Level;
}


void GAMEDATA::setCurrentWave(int wave){
	currentWave =wave;
}

int GAMEDATA::getCurrentWave(){
	return currentWave;
}


void GAMEDATA::initLevelInfo(int Level){
	initPlayerGold(Level);
	initLifeValue(Level);
}

void GAMEDATA::clean(){
	//if(!towers.empty()){towers.clear();}
	if(!waypoints.empty()){waypoints.clear();}
	if(!targets.empty()){targets.clear();}
	if(!waves.empty()){waves.clear();}
	if(!projectiles.empty()){projectiles.clear();}
	currentWave=0;
}

int GAMEDATA::getPriceByImageName(String s){
	if(s.compare("machinegunturret.png")==0){
		return 50;
	}else if(s.compare("tower_damage.png")==0){
		return 80;
	}
	return 0;
} 