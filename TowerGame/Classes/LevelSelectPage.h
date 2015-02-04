#ifndef _LEVELSELECTPAGE__
#define _LEVELSELECTPAGE__
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class LevelSelectPage: public Node
{
public:
    
    bool initLevelPage(const std::string& bgName, int level);
    static LevelSelectPage* create(const std::string& bgName, int level);
    void menuStartCallback(Ref* pSender);
};

#endif