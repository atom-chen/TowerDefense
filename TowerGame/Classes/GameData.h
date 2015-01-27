#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();

private:
	GAMEDATA();
	void init();

private:
	static GAMEDATA* _instance;
};
#endif
