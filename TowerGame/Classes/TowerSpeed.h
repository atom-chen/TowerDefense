#ifndef _TOWERSPEED_H_
#define _TOWERSPEED_H_
#include "Tower.h"

class TowerSpeed : public Tower 
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
