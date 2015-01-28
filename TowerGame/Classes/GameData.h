#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();

	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();

	void initLifeValue(int Level);
	void initPlayerGold(int level);

	//life value
	void setLifeValue(int value);
	int getLifeValue();

	//player gold
	void setPlayerGold(int gold);
	int getPlayerGold();

	//level number
	int getCurrentLevel();
	void seturrentLevel(int level);

private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int playerGold;
	int lifeValue;
	int Level;
};

#endif
