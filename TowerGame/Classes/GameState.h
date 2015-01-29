#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class GAMESTATE{
public:
	static GAMESTATE* getInstance();
	void reset();
	void checkGameOver();
	void setGamePause(bool pause);
	bool getGamePause();
	void setGameOver(bool over);
	bool getGameOver();
	void setRefreshTopmenu(bool refresh);
	bool getRefreshTopmenu();
    void setLevelResult(bool pass);
	bool getLevelResult();
	void setRefreshGameHUD(bool refresh);
	bool getRefreshGameHUD();
	void setNeedRefesh(bool refresh);
private:
	GAMESTATE();
	void init();
	static GAMESTATE* _instance;
	bool gamePause;
	bool gameOver;
	bool refreshTopmenu;
	bool refreshGameHUD;
	bool levelResult;
};
#endif