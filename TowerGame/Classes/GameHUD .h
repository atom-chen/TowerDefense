#ifndef _GAMEHUD_H_
#define _GAMEHUD_H_
#include "cocos2d.h"

USING_NS_CC;

class GameHUD: public Layer 
{
public:
	Sprite* background;
	Sprite* selSpriteRange;
	Sprite* selSprite;
	Vector<Sprite*> movableSprites;
	virtual bool init();
	CREATE_FUNC(GameHUD);
	virtual void onEnter();
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
};
#endif