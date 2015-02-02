#include "Projectile.h"

int Projectile::typeOfBullet =0;
Projectile* Projectile::projectile(int type)
{
	Projectile* projectile = (Projectile*)Sprite::create("projectile.png");
	typeOfBullet=type;
	if (projectile != NULL)
	{
		return projectile;
	}
	return NULL;
}


int Projectile::getBulletType(){
	return typeOfBullet;
}