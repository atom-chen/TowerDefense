#ifndef _TOWERDAMAGE_H_
#define _TOWERDAMAGE_H_

#include "Tower.h"

class TowerDamage : public Tower 
{
public:
	Projectile* nextProjectile;
	static Tower* tower();
	bool virtual init();
	void towerLogic(float dt);
	void finishFiring();
	void creepMoveFinished(Node* sender);
};
#endif