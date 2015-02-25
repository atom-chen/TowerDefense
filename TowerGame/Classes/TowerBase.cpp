#include "TowerBase.h"
#include "GameData.h"

TowerBase::TowerBase()
:scope(0)
,towerValue(0)
,lethality(0)
,rate(0)
,nearestEnemy(NULL)
{
}

bool TowerBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    scheduleUpdate();
	return true;
}


void TowerBase::checkNearestEnemy()
{
    GAMEDATA *instance = GAMEDATA::getInstance();
    auto enemyVector = instance->enemyVector;
    
	auto currMinDistant = this->scope;
    
    EnemyBase *enemyTemp = NULL;
	for(int i = 0; i < enemyVector.size(); i++)
	{
		auto enemy = enemyVector.at(i);
		double distance = this->getPosition().getDistance(enemy->sprite->getPosition());
        
		if (distance < currMinDistant) {
			currMinDistant = distance;
            enemyTemp = enemy;
		}
	}
    nearestEnemy = enemyTemp;
}






