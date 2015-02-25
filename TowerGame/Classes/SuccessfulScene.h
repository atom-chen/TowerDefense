#ifndef __SUCCESSFULSCENE_H__
#define __SUCCESSFULSCENE_H__

#include <iostream>
#include "cocos2d.h"

class SuccessfulScene : public cocos2d::Scene
{
public:  

    virtual bool init();  
     
    void menuNextCallback(Ref* pSender);  
	void menuCloseCallback(Ref* pSender); 
	CREATE_FUNC(SuccessfulScene); 
private:

}; 
#endif 
