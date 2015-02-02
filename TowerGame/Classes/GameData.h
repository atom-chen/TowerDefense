#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include"Tower.h"
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
	//Vector<Tower*> towers;
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
	int getCurrentLevel();
	void setCurrentLevel(int level);
	//waves 
	int getCurrentWave();
	void setCurrentWave(int wave);

	void initLifeValue(int Level);
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
