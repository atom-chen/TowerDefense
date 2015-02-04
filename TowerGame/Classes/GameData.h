#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include"TowerBase.h"
#include"Projectile.h"
#include"Wave.h"
#include"Creep.h"
#include"WayPoint.h"

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	Vector<WayPoint*> waypoints;
	Vector<Creep*> targets;
	Vector<Wave*> waves;
	Vector<TowerBase*> towers;
	Vector<Projectile*> projectiles;
	void clean();
	int getPriceByImageName(String s);
	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();
	//init level info
	void initLevelInfo(int level);
	//life value
	void setLifeValue(int value);
	int getLifeValue();
	//player gold
	void setPlayerGold(int gold);
	int getPlayerGold();
	//level number
	int getMaxLevel();
	void setMaxLevel(int level);
	int getCurrentLevel();
	void setCurrentLevel(int level);

    //
	 void setNextLevelFile(std::string filename);
	 std::string getNextLevelFile();
	//waves 
	int getCurrentWave();
	void setCurrentWave(int wave);
	//player life value
	void initLifeValue(int Level);
    //change tower proprity
	void doubleTowerRange();
	int getTowerRange();
	void doubleTowerFrequency();
	float getTowerFrequency();

private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int playerGold;
	int lifeValue;
	int Level;
	int currentWave;
	//int towerRange;
	//int towerFrequency;
	void initPlayerGold(int level);

};

#endif
