#include "Tower.h"
#include "DataModel.h"

Tower* TowerSpeed::towerSpeed()
{
	Tower* tower = Tower::create();
	tower->sprite = Sprite::create("MachineGunTurret.png");
	tower->addChild(tower->sprite, 0);
	tower->range = 200;
	tower->schedule(schedule_selector(towerLogic), 0.2);
	return tower;
}

bool TowerSpeed::init()
{
	if (!Sprite::init()) 
	{
		return false;
	}
	return true;
}

void TowerSpeed::towerLogic(float dt)
{
	this->target = this->getClosesTarget();

	if (this->target != NULL) 
	{
		// Rotate player to face shooting direction
		Point shootVector = this->target->getPosition() - this->getPosition();
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

		float rotateSpeed = 0.5 / M_PI;
		float rotateDuration = fabs(shootAngle * rotateSpeed);

		this->runAction(Sequence::create(RotateTo::create(rotateDuration,cocosAngle),NULL));

		this->runAction(Sequence::create(RotateTo::create(rotateDuration, cocosAngle), CallFunc::create(this, callfunc_selector(TowerSpeed::finishFiring)), NULL));
	}
}

void TowerSpeed::finishFiring()
{
	DataModel *m = DataModel::getModel();

	if (this->target != NULL && this->target->curHp > 0 && this->target->curHp < 100)
	{
		this->nextProjectile = Projectile::projectile();
		this->nextProjectile->setPosition(this->getPosition());

		this->getParent()->addChild(this->nextProjectile, 1);
		m->projectiles.pushBack(this->nextProjectile);

		float delta = 1.0f;
		Point shootVector = -(this->target->getPosition() - this->getPosition());
		Point normalizedShootVector = ccpNormalize(shootVector);
		Point overshotVector = normalizedShootVector * 320;
		Point offscreenPoint = (this->getPosition() - overshotVector);

		this->nextProjectile->runAction(Sequence::create(MoveTo::create(delta, offscreenPoint), CallFuncN::create(this, callfuncN_selector(TowerSpeed::creepMoveFinished)), NULL));

		this->nextProjectile->setTag(2);

		this->nextProjectile = NULL;

	}
}

void TowerSpeed::creepMoveFinished(Node* sender)
{
	DataModel * m = DataModel::getModel();
	Sprite *sprite = (Sprite *)sender;
	this->getParent()->removeChild(sprite,true);

	m->projectiles.eraseObject((Projectile*)sprite);
}