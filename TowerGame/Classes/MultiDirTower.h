#ifndef __MULTIDIRTOWER_H__
#define __MULTIDIRTOWER_H__

#include "TowerBase.h"


class MultiDirTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(MultiDirTower);
    
    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* MultiDirTowerBullet();
    void createBullet6(float dt);
private:
    Sprite* tower;
    
};

#endif
