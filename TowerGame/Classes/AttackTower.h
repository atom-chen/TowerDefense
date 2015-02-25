#ifndef __ATTACKTOWER_H__
#define __ATTACKTOWER_H__

#include "TowerBase.h"

class AttackTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(AttackTower);

    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* AttackTowerBullet();
    
private:
    Sprite* tower;
    
};

#endif 
