#ifndef _TOWERSPEED_H_
#define _TOWERSPEED_H_
#include "TowerBase.h"
#include "Projectile.h"
#include "cocos2d.h"

class TowerSpeed : public TowerBase 
{
public:
    virtual bool init() ;
    CREATE_FUNC(TowerSpeed);
	Projectile* nextProjectile;
    void towerLogic(float dt);
	void finishFiring();
	void creepMoveFinished(Node* sender);
    
private:
    Sprite* tower;
};
#endif