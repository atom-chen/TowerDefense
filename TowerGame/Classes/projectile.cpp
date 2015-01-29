#include "Projectile.h"

Projectile* Projectile::projectile()
{
	Projectile* projectile = (Projectile*)Sprite::create("projectile.png");
	if (projectile != NULL)
	{
		return projectile;
	}
	return NULL;
}