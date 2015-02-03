#ifndef _TOWER_H_
#define _TOWER_H_
#include "cocos2d.h"
#include "Creep.h"
#include "Projectile.h"

class Tower: public Sprite 
{
public:
	int range;
	Sprite* sprite;
	Creep* target;
	Sprite * selSpriteRange;
	Creep* getClosesTarget();
	CREATE_FUNC(Tower);
};

class TowerSpeed : public Tower 
{
public:
	Projectile* nextProjectile;
	static Tower* towerSpeed();
	bool virtual init();
    void towerLogic(float dt);
	void finishFiring();
	void creepMoveFinished(Node* sender);
};

class TowerDamage : public Tower 
{
public:
	Projectile* nextProjectile;
	static Tower* towerDamage();
	bool virtual init();
    void towerLogic(float dt);
	void finishFiring();
	void creepMoveFinished(Node* sender);
};

#endif