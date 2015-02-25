#ifndef __FAILEDSCENE_H__
#define __FAILEDSCENE_H__

#include <iostream>
#include "cocos2d.h"

class FailedScene : public cocos2d::Scene
{
public:  

    virtual bool init();  
    CREATE_FUNC(FailedScene);  
    void menuBackCallback(Ref* pSender);  

}; 
#endif 
