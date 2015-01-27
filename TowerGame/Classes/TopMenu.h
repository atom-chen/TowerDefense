#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class TopMenu : public Node {
public:
	static TopMenu* getInstance();
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void updatePlayerGold(int gameGold);
	void pauseGame();
private:
	static TopMenu* _instance;
	TopMenu();
	void LoadTopMenu();
private:
	Label* lifeValue;
	Label* waveValue;
	Label* playerGold;

};
#endif