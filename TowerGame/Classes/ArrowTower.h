#ifndef __ARROWTOWERR_H__
#define __ARROWTOWERR_H__

#include "TowerBase.h"


class ArrowTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(ArrowTower);

    void rotateAndShoot(float dt);
    void shoot();
    void removeBullet(Node* pSender);
    Sprite* ArrowTowerBullet();
    
private:
    Sprite* rotateArrow;
    
};

#endif 
