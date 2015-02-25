#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include"TowerBase.h"
#include"Wave.h"
#include"WayPoint.h"
#include "GroupEnemy.h"

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	 Vector<EnemyBase*> enemyVector;
    Vector<Sprite*> bulletVector;
    Vector<TowerBase*> towerVector;
    Vector<GroupEnemy*> groupVector;
	void clear();
	int getPriceByImageName(String s);
	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();

    //change tower proprity
	void doubleTowerRange();
	int getTowerRange();
	void doubleTowerFrequency();
	float getTowerFrequency();

	CC_SYNTHESIZE(std::string, curBgName, CurBgName);
    CC_SYNTHESIZE(std::string, curMapName, CurMapName);
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, groupNum, GroupNum);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);

private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int playerGold;
	int lifeValue;
	int Level;
	int currentWave;
	void initPlayerGold(int level);

};

#endif
