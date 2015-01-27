#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include <string>
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;
class GameLayer;

class TopMenu : public Node{
public:
	static TopMenu* create(GameLayer* layer);
	virtual bool init(GameLayer* layer);

private:
	Label* lifeValue;
	Label* waveValue;
	Label* playerGold;
private:
	void LoadTopMenu();

};
#endif