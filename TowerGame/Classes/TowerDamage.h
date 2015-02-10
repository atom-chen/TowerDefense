#ifndef _TOWERDAMAGE_H_
#define _TOWERDAMAGE_H_
#include "TowerBase.h"
#include "Projectile.h"
#include "cocos2d.h"

class TowerDamage : public TowerBase 
{
public:
	Projectile* nextProjectile;
	bool virtual init();
    void towerLogic(float dt);
	void finishFiring();
	void creepMoveFinished(Node* sender);
};
#endif