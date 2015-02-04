#ifndef _LEVELSCENE_H_
#define _LEVELSCENE_H_

#include <iostream>
#include "cocos2d.h"

class LevelScene : public cocos2d::Scene
{
public:  

    virtual bool init();  
    CREATE_FUNC(LevelScene);
    static LevelScene *getInstance();
    
private:
    static LevelScene *instance;
}; 
#endif
