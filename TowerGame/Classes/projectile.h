#pragma once
#include "cocos2d.h"

USING_NS_CC;
enum BulletType
{
	SPEED,
	DAMAGE
};
class Projectile: public Sprite 
{
public:
	static Projectile* projectile(int type);
	void setBullType(int type);
	int getBulletType();
private:
	static int typeOfBullet;
};
