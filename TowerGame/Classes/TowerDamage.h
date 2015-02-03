#ifndef _TOWERDAMAGE_H_
#define _TOWERDAMAGE_H_
#include "TowerBase.h"
#include "Projectile.h"

class TowerDamage : public TowerBase 
{
public:
	
	virtual bool init() ;
    CREATE_FUNC(TowerDamage);
	Projectile* nextProjectile;
    void towerLogic(float dt);
	void finishFiring();
	void creepMoveFinished(Node* sender);
};
#endif