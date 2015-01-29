#pragma once
#include "cocos2d.h"
#include "WayPoint.h"
#include "Creep.h"
#include "Tower.h"
#include "projectile.h"
#include "GameHUD .h"
#include "GameLayer.h"

USING_NS_CC;

class DataModel 
{
public:
	GameLayer* _gameLayer;
	GameHUD* _gameHUDLayer;
	Vector<WayPoint*> waypoints;
	Vector<Creep*> targets;
	Vector<Wave*> waves;
	Vector<Tower*> towers;
	Vector<Projectile*> projectiles;
	void clean();
	static DataModel* getModel();
private:
	DataModel(){};
	static DataModel * m_pInstance;
};