#ifndef _TOWER_H_
#define _TOWER_H_
#include "cocos2d.h"
#include "Creep.h"
#include "Projectile.h"

class TowerBase: public Sprite 
{
public:
    virtual bool init();
	CREATE_FUNC(TowerBase);
	int range;
	Creep* target;
	Creep* getClosesTarget();	

protected:
	 Creep* nearestEnemy;  

};

#endif