#ifndef _LEVELSELECTLAYER_H_
#define _LEVELSELECTLAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class LevelSelectLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(LevelSelectLayer);
	void goBack();
	void startGame();
private:
	//TODO need add
};
#endif
