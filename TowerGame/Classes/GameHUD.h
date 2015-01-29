#ifndef _GAMEHUD_H_
#define _GAMEHUD_H_
#include "cocos2d.h"
#include "GameLayer.h"
#include "cocos2d.h"

USING_NS_CC;

class GameLayer;

class GameHUD: public Node 
{
public:
	static GameHUD* create(GameLayer* layer);
	virtual bool init(GameLayer* layer);
	Sprite* background;
	Sprite* selSpriteRange;
	Sprite* selSprite;
	Vector<Sprite*> movableSprites;
	virtual void onEnter();
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
private:
	GameLayer* m_layer;
};
#endif