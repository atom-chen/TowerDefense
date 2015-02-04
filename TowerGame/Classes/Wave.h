#pragma  once
#include "cocos2d.h"
#include "Creep.h"

USING_NS_CC;

class Wave :public Node
{
public:
	Point position;
	double spawnRate;
	Creep* creepType;
	virtual bool init();
	Wave* initCreepWave(int type1Total, int type1Hp, int type2Total, int type2Hp, int type3Total, int type3Hp );
	CREATE_FUNC(Wave);
	CC_SYNTHESIZE(int, type1Total, Type1Total);
    CC_SYNTHESIZE(int, type2Total, Type2Total);
    CC_SYNTHESIZE(int, type3Total, Type3Total);
    CC_SYNTHESIZE(int, type1Hp, Type1Hp);
    CC_SYNTHESIZE(int, type2Hp, Type2Hp);
    CC_SYNTHESIZE(int, type3Hp, Type3Hp);
    CC_SYNTHESIZE(int, totalCreeps, totalCreeps);
    CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
};