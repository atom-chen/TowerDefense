#ifndef __LOADLEVELINFO_H__
#define __LOADLEVELINFO_H__

#include "cocos2d.h"
using namespace cocos2d;

class LoadLevelinfo: public Ref
{
public:
    
    ~LoadLevelinfo();
    static LoadLevelinfo * createLoadLevelinfo(const std::string& plistpath);
    
    bool initPlist(const std::string& plistpath);
	void readLevelInfo();
    void clearAll();
    
private:
    ValueMap resources;
    ValueMap levelInfo;
};
#endif
